#include "pch.h"
#include "../ImageFifo/ImageFifo.h"
#include "gtest-memleak.h"

void reader(ImageFifo &fifo, std::istream &in, bool& sync) {

	int* data = nullptr;
	int i;
	while (in >> i) {
		while (data == nullptr)
			data = static_cast<int*>(fifo.getFree());
		fifo.addReady(data);
		data = nullptr;
	}
	sync = true;
}

void writer(ImageFifo &fifo, std::ostream &out, bool& sync) {
	int* data = nullptr;
	while (!sync) {

		size_t size;
		while (data == nullptr && (!sync))
			data = static_cast<int*>(fifo.getReady());
		if (data != nullptr)
			out << data << " ";
		fifo.addFree(data);
		data = nullptr;
	}
}
TEST(FifoTest, AvarageValues) {

	ImageFifo queue(sizeof(int), 4);

	int* s = static_cast<int*>(queue.getFree());
	*s = 4;
	queue.addReady(s);
	s = static_cast<int*>(queue.getReady());
	ASSERT_TRUE(*s == 4);
	queue.addFree(s);

	s = static_cast<int*>(queue.getFree());
	*s = 10;
	queue.addReady(s);
	s = static_cast<int*>(queue.getReady());
	ASSERT_TRUE(*s == 10);
	queue.addFree(s);
}

TEST(FifoTestTwoThread, AvarageValues) {
	std::istringstream in("1 2");
	std::ostringstream out;

	ImageFifo fifo(sizeof(int), 4);

	bool sync = false;
	std::thread read(reader, std::ref(fifo), std::ref(in), std::ref(sync));
	std::thread write(writer, std::ref(fifo), std::ref(out), std::ref(sync));

	read.join();
	write.join();

	ASSERT_TRUE(out.str() == "1 2");
}

GTEST_API_ int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}