# Homebrew formula for Plain.
# Publish it from a tap repository named homebrew-plain (see README.md next to this file);
# then: brew install iamsabroy-gif/plain/plain
class Plain < Formula
  desc "Programming language that reads like English, for learning to program"
  homepage "https://github.com/iamsabroy-gif/plain"
  head "https://github.com/iamsabroy-gif/plain.git", branch: "main"
  # RELEASE (filled in by tools/update-formula.sh)

  def install
    system "make", "CXX=#{ENV.cxx}"
    bin.install "build/plain"
  end

  test do
    assert_equal "42", shell_output("#{bin}/plain -e 'say 6 * 7'").strip
    (testpath/"hello.plain").write("set name to \"Brew\"\nsay \"Hello {name}\"\n")
    assert_equal "Hello Brew", shell_output("#{bin}/plain #{testpath}/hello.plain").strip
  end
end
