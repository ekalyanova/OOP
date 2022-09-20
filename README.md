There are some OOP projects(code only) written on C++ with unit-tests.

Here is short description for each of them:


skiplist - The Skip list data structure was implemented. The class interface is similar to the std::map interface, with the same template parameters. An iterator is also implemented and MANY unit-tests are written.


BubbleTemplate - Bubble sort on templates. 


Football - A system for storing information about the football championship. The information is based on the following main classes: Team, Player, Match. These classes are related to each other through aggregation, association, etc. There are many design patterns applied here.


ImageFifo - Developed class that allows multithreaded buffered data reading. Data is read/written in fixed-size blocks. A typical example of such data is a sequence of uncompressed images of the same size (for example, in bmp format).

Two execution threads are supposed to work simultaneously: one reader thread reads data into the queue, the second writer thread checks the queue with some frequency, selects the next data from it, and writes them to files.

The queue plays the role of a regulator here, which: allows you to coordinate the speed of reading and writing data between threads, guarantees the order and integrity of the transmitted data, synchronizes access to data from different execution threads.

The queue class is designed within the framework of the RAII concept, and is the owner of the data buffer.


DataFIFO - The same requirements as for ImageFIFO but Data is read in blocks of arbitrary size, an arbitrary number of blocks at a time.


simpleblur - Using the OpenCV library, local image blurring is implemented. 


SharedWhiteboard - A shared drawing board using OpenCV (graphics) and SFML (network) was implemented.

The server program accepts connections and stores the image of the board. Clients receive the full image of the board when they first connect, after that the server simply redirects them drawing commands received from other clients.

Clients, after connecting to the server, display the resulting image and allow you to perform the simplest drawing operations (line, rectangle, text). Each operation is encoded and sent to the server, which applies it to its image, and also sends it to clients. In this scheme, only changes are sent over the network, and their server and clients are applied individually