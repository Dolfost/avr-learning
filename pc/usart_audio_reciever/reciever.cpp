#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include <QSerialPort>

void write_wav_header(std::ofstream &out,
											uint32_t sample_rate,
											uint16_t bits_per_sample,
											uint16_t num_channels,
											uint32_t num_samples)
{
    uint32_t byte_rate = sample_rate * num_channels * bits_per_sample / 8;
    uint16_t block_align = num_channels * bits_per_sample / 8;
    uint32_t data_chunk_size = num_samples * block_align;
    uint32_t fmt_chunk_size = 16;
    uint32_t riff_chunk_size = 4 + (8 + fmt_chunk_size) + (8 + data_chunk_size);

    out.write("RIFF", 4);
    out.write(reinterpret_cast<const char *>(&riff_chunk_size), 4);
    out.write("WAVE", 4);

    out.write("fmt ", 4);
    out.write(reinterpret_cast<const char *>(&fmt_chunk_size), 4);

    uint16_t audio_format = 1; // PCM
    out.write(reinterpret_cast<const char *>(&audio_format), 2);
    out.write(reinterpret_cast<const char *>(&num_channels), 2);
    out.write(reinterpret_cast<const char *>(&sample_rate), 4);
    out.write(reinterpret_cast<const char *>(&byte_rate), 4);
    out.write(reinterpret_cast<const char *>(&block_align), 2);
    out.write(reinterpret_cast<const char *>(&bits_per_sample), 2);

    out.write("data", 4);
    out.write(reinterpret_cast<const char *>(&data_chunk_size), 4);
}

int main(int argc, const char** argv) { 
	QSerialPort input(argv[1]);
	input.setPortName(argv[1]);
	input.setBaudRate(9600);
	input.setDataBits(QSerialPort::DataBits::Data8);
	input.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
	input.setStopBits(QSerialPort::StopBits::OneStop);

	std::ofstream output(argv[2]);

	if (not input.isOpen()) { 
		std::cerr << "Could not open input device: " << argv[1] << std::endl;
		return 1;
	}
	if (not output.is_open()) { 
		std::cerr << "Could not open output file: " << argv[2] << std::endl;
		return 1;
	}

	uint32_t sr = 44100;
	uint32_t seconds = 2;
	char sample;
	write_wav_header(output, sr, 8, 1, sr*seconds);
	std::vector<uint8_t> samples;
	samples.reserve(sr*seconds);
	for (uint32_t i = 0; i < seconds*(uint32_t)sr; ++i) {
		while (not input.read(&sample, 1)) {}
		samples.push_back(sample);
		std::cout << (int)samples.back() << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(22));
	}
	input.close();

	for (uint32_t i = 0; i < seconds*sr; ++i) {
		output.write(reinterpret_cast<const char *>(samples[i]), 1);
	}

	output.close();
	std::cout << "WAV file written: " << argv[2] << std::endl;

	return 0;
}
