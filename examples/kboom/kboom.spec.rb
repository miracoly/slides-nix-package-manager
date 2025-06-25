require 'open3'

BIN = ENV.fetch('BIN', File.expand_path('main.out', __dir__))

RSpec.describe 'kboom CLI' do
  # Helper to run `kboom <args…>` and capture stdout, stderr, status
  def run_kboom(*args)
    Open3.capture3(BIN, *args.map(&:to_s))
  end

  describe 'happy paths' do
    it 'computes factorial 5 = 120' do
      stdout, stderr, status = run_kboom('factorial', 5)
      expect(status.exitstatus).to eq(0)
      expect(stderr).to eq('')
      expect(stdout.chomp).to eq('120')
    end

    it 'computes fibonacci 10 = 55' do
      stdout, = run_kboom('fibonacci', 10)
      expect(stdout.chomp).to eq('55')
    end

    it 'computes sum of squares 5 = 55' do
      out, = run_kboom('sumsquare', 5)
      expect(out.chomp).to eq('55')
    end

    it 'accepts short aliases (fa, fi, s)' do
      out1, = run_kboom('fa', 6)
      out2, = run_kboom('fi', 11)
      out3, = run_kboom('s',  3)
      expect(out1.chomp).to eq('720')   # 6!
      expect(out2.chomp).to eq('89')    # F₁₁
      expect(out3.chomp).to eq('14')    # 1²+2²+3²
    end
  end

  describe 'error handling' do
    it 'rejects negative numbers' do
      _out, err, status = run_kboom('fa', -3)
      expect(status.exitstatus).to_not eq(0)
      expect(err).to match(/Error.*non-negative/i)
    end

    it 'rejects unknown sub-commands' do
      _out, err, status = run_kboom('foo', 7)
      expect(status.exitstatus).to_not eq(0)
      expect(err).to match(/unknown command/i)
    end
  end
end
