// Every algorithm in the playground's gallery (web/algorithms.js): it is in the standard style, it
// gives the right answer, it records fully under "Watch it run" (no error, not cut short), and every
// line of it has a box in its flowchart.
//   node tests/algorithms_test.js
const { spawnSync } = require("child_process");
const fs = require("fs"), path = require("path"), os = require("os");
const ROOT = path.join(__dirname, ".."), PLAIN = path.join(ROOT, "build", "plain");
const ALGORITHMS = require(path.join(ROOT, "web", "algorithms.js"));
const Flow = require(path.join(ROOT, "web", "flowchart.js"));
const TMP = fs.mkdtempSync(path.join(os.tmpdir(), "plain-alg-"));
const expected = {
  biggest: "The biggest is 9",
  "linear-search": "Found 9 at position 5",
  "binary-search": "Found 23 at position 6",
  "bubble-sort": "[1, 2, 3, 4, 5, 8]",
  "selection-sort": "[10, 13, 14, 29, 37]",
  "insertion-sort": "[1, 2, 3, 5, 6, 7]",
  "merge-sort": "[3, 9, 10, 27, 38, 43, 82]",
  "quick-sort": "[10, 30, 40, 50, 70, 80, 90]",
  fibonacci: "fib(5) is 5",
  hanoi: "Move disc 1 from A to C",
  bfs: 'Visited in order: ["Home", "Park", "School", "Shop", "Library"]',
  dfs: 'Visited in order: ["Home", "Park", "Shop", "Library", "School"]',
  brackets: "([]{()}) balanced: true",
  gcd: "The greatest common divisor is 6",
};
let failed = 0;
const fail = (msg) => { failed++; console.log("FAILED (algorithms): " + msg); };
const ids = new Set();
for (const a of ALGORITHMS) {
  if (ids.has(a.id)) fail("two algorithms are called " + a.id);
  ids.add(a.id);
  for (const k of ["name", "picture", "group", "cost", "about", "code"]) if (!a[k]) fail(a.id + " has no " + k);
  const file = path.join(TMP, a.id + ".plain");
  fs.writeFileSync(file, a.code);
  const fmt = spawnSync(PLAIN, ["format", "--check", file], { encoding: "utf8" });
  if (fmt.status !== 0) fail(a.id + " is not in the standard style: " + fmt.stdout + fmt.stderr);
  const run = spawnSync(PLAIN, [file], { encoding: "utf8", timeout: 20000 });
  if (run.status !== 0) fail(a.id + " stopped with a problem: " + run.stdout + run.stderr);
  if (!(a.id in expected)) fail(a.id + " has no expected answer in this test");
  else if (!run.stdout.includes(expected[a.id])) fail(a.id + " said " + JSON.stringify(run.stdout.trim()) + ", expected it to include " + JSON.stringify(expected[a.id]));
  const viz = spawnSync(PLAIN, ["visualize", "--json", "-e", a.code], { encoding: "utf8", maxBuffer: 1 << 28 });
  let trace = null;
  try { trace = JSON.parse(viz.stdout); } catch (e) { fail(a.id + ": visualize gave no trace " + viz.stderr); continue; }
  if (trace.error) fail(a.id + ": the recording stopped with " + JSON.stringify(trace.error));
  if (trace.truncated) fail(a.id + ": too long to record in full (" + trace.steps.length + " steps); use a smaller input");
  if (trace.steps.length < 10) fail(a.id + ": only " + trace.steps.length + " steps recorded");
  // every step of the main file lands on a box of the flowchart
  const chart = Flow.svg(a.code);
  const lost = [...new Set(trace.steps.filter((s) => s.fi === 0 && !Flow.boxForLine(chart.boxes, s.l)).map((s) => s.l))];
  const lastLine = a.code.replace(/\n$/, "").split("\n").length;
  const realLost = lost.filter((l) => l !== lastLine);   // (the very last step is the program ending)
  if (realLost.length) fail(a.id + ": steps on lines " + realLost.join(", ") + " have no box in the flowchart");
}
fs.rmSync(TMP, { recursive: true, force: true });
if (failed) process.exit(1);
console.log("algorithms: ok (" + ALGORITHMS.length + " algorithms run, recorded and charted)");
