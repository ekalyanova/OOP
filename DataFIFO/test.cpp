#include "pch.h"
#include  "../DataFIFO/DataFIFO.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
void reader(DataFIFO &fifo, std::istream &in, bool& sync) {

	char* data = nullptr;
	std::string str;
	while (in >> str) {
		while (data == nullptr)
			data = static_cast<char*>(fifo.getFree(str.size() + 1));                   //+1? \0?
		std::copy(str.c_str(), str.c_str() + str.size() + 1, data);
		fifo.addReady(data);
		data = nullptr;
	}
	sync = true;
}

void writer(DataFIFO &fifo, std::ostream &out, bool& sync) {

	char* data = nullptr;
	while (!sync || !fifo.isEmpty()) {

		size_t size;
		while (data == nullptr && (!sync || !fifo.isEmpty()))
			data = static_cast<char*>(fifo.getReady(size));
		if (data != nullptr)
			out << data << " ";
		fifo.addFree(data);
		data = nullptr;
	}
}

TEST(DataFIFOMultiTest, myOwnText) {

	std::istringstream in("My own super informatively text, so, i suppose my fantasy is not enought to do it, but im ready to try again and again");
	std::ostringstream out;

	DataFIFO fifo(1000, 10);

	bool sync = false;
	std::thread read(reader, std::ref(fifo), std::ref(in), std::ref(sync));
	std::thread write(writer, std::ref(fifo), std::ref(out), std::ref(sync));

	read.join();
	write.join();

	ASSERT_TRUE(out.str() == "My own super informatively text, so, i suppose my fantasy is not enought to do it, but im ready to try again and again ");
}


TEST(DataFIFOMultiTest, empty) {

	std::istringstream in("");
	std::ostringstream out;

	DataFIFO fifo(1000, 10);

	bool sync = false;
	std::thread read(reader, std::ref(fifo), std::ref(in), std::ref(sync));
	std::thread write(writer, std::ref(fifo), std::ref(out), std::ref(sync));

	read.join();
	write.join();

	ASSERT_TRUE(out.str() == "");
}
