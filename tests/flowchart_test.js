// The flowchart engine (web/flowchart.js): it reads every Plain program in the repository without
// trouble, gives every line of code a box, never draws two boxes on top of each other, and gets the
// shape of a known program right. Half-typed programs must not break it (it redraws as you type).
//   node tests/flowchart_test.js
const fs = require("fs"), path = require("path");
const { execFileSync } = require("child_process");
const ROOT = path.join(__dirname, "..");
const Flow = require(path.join(ROOT, "web", "flowchart.js"));
let failed = 0, programs = 0, boxes = 0;
const fail = (msg) => { failed++; console.log("FAILED (flowchart): " + msg); };

function checkProgram(name, code) {
  programs++;
  let r;
  try { r = Flow.svg(code); } catch (e) { fail(name + ": " + e.message); return; }
  boxes += r.boxes.length;
  if (!/^<svg[\s\S]*<\/svg>$/.test(r.svg)) fail(name + ": not an SVG");
  // every line that does something has a box (block lines like end / otherwise / define are drawn as the shape around them)
  code.split("\n").forEach((line, i) => {
    const c = line.replace(/#.*$/, "").trim();
    if (!c || /^note:/i.test(c) || /^(end|otherwise|class\b.*|define\b.*|init\b.*|on error\b.*|[\]})].*)$/i.test(c)) return;
    if (!Flow.boxForLine(r.boxes, i + 1)) fail(name + ": line " + (i + 1) + " has no box: " + c);
  });
  // no two boxes overlap
  const b = r.boxes;
  for (let i = 0; i < b.length; i++)
    for (let j = i + 1; j < b.length; j++) {
      const p = b[i], q = b[j];
      if (p.x < q.x + q.w - 1 && q.x < p.x + p.w - 1 && p.y < q.y + q.h - 1 && q.y < p.y + p.h - 1)
        fail(name + ": boxes overlap: " + JSON.stringify(p.text) + " and " + JSON.stringify(q.text));
    }
  for (const x of b) if (x.x < 0 || x.y < 0 || x.x + x.w > r.width + 1 || x.y + x.h > r.height + 1) fail(name + ": a box is outside the picture: " + x.text);
}

// every program in the repository
const files = [];
for (const dir of ["examples", "lib", "lib/problems", "tests/cases", "tests/apps"])
  for (const f of fs.readdirSync(path.join(ROOT, dir))) if (f.endsWith(".plain")) files.push(path.join(dir, f));
for (const f of files) checkProgram(f, fs.readFileSync(path.join(ROOT, f), "utf8"));
const lessons = JSON.parse(execFileSync(path.join(ROOT, "build", "plain"), ["lesson", "--json"], { encoding: "utf8" })).lessons;
for (const L of lessons) L.exercises.forEach((ex, i) => checkProgram("lesson " + L.number + "." + (i + 1), ex.solution));

// the shape of a known program
const known = Flow.parse([
  "set total to 0",
  "for i from 1 to 3",
  "    if i is 2 then",
  "        skip",
  "    otherwise if i is 9 then",
  "        stop",
  "    otherwise",
  "        increase total by i",
  "    end",
  "end",
  "define double with x",
  "    give back x * 2",
  "end",
  "say double(total)",
].join("\n"));
const shape = known.main.map((it) => it.k).join(" ");
if (shape !== "do loop do") fail("main program shape: " + shape);
const loop = known.main[1];
if (loop.body.length !== 1 || loop.body[0].k !== "if" || loop.body[0].branches.length !== 2 || !loop.body[0].other) fail("if / otherwise if / otherwise inside the loop");
if (loop.body[0].branches[0].body[0].kind !== "skip" || loop.body[0].branches[1].body[0].kind !== "stop") fail("skip and stop");
if (known.actions.length !== 1 || known.actions[0].body[0].kind !== "give") fail("the action and its give back");
if (known.main[2].io !== "out") fail("say is drawn as output");

// half-typed programs
for (const bad of ["if x then", "end\nend\nsay 1", "for i from 1 to", "otherwise\nsay 2", "", "class", "try\nsay 1", "define", "set xs to [1,\n2", "on error x", "say \"unclosed", "while\n\n\nend"])
  try { Flow.svg(bad); } catch (e) { fail("half-typed program " + JSON.stringify(bad) + ": " + e.message); }

if (failed) process.exit(1);
console.log("flowchart: ok (" + programs + " programs, " + boxes + " boxes, no overlaps)");
