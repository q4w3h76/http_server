TARGET = simpver
OBJECT_DIR = ./build/object/
DEBUG_DIR = ./build/debug/
SRC_DIR = ./src/
FLAGS_DEBUG = -g -Wall
FLAGS_LIBRARY = -lpthread 


all: $(TARGET)

$(TARGET): main.o server.o listener.o worker.o client.o response.o
	g++ $(OBJECT_DIR)main.o $(OBJECT_DIR)server.o $(OBJECT_DIR)listener.o $(OBJECT_DIR)worker.o $(OBJECT_DIR)client.o $(OBJECT_DIR)response.o $(FLAGS_LIBRARY) $(FLAGS_DEBUG) -o $(DEBUG_DIR)$(TARGET)

main.o: $(SRC_DIR)main.cpp
	g++ -o $(OBJECT_DIR)main.o $(FLAGS_DEBUG) -c $(SRC_DIR)main.cpp

server.o: $(SRC_DIR)server.cpp
	g++ -o $(OBJECT_DIR)server.o $(FLAGS_DEBUG) -c $(SRC_DIR)server.cpp

listener.o: $(SRC_DIR)listener.cpp
	g++ -o $(OBJECT_DIR)listener.o $(FLAGS_DEBUG) -c $(SRC_DIR)listener.cpp

worker.o: $(SRC_DIR)worker.cpp
	g++ -o $(OBJECT_DIR)worker.o $(FLAGS_DEBUG) -c $(SRC_DIR)worker.cpp

client.o: $(SRC_DIR)client.cpp
	g++ -o $(OBJECT_DIR)client.o $(FLAGS_DEBUG) -c $(SRC_DIR)client.cpp

response.o: $(SRC_DIR)response.cpp
	g++ -o $(OBJECT_DIR)response.o $(FLAGS_DEBUG) -c $(SRC_DIR)response.cpp

clean:
	rm -rf $(OBJECT_DIR)*.o $(DEBUG_DIR)$(TARGET)
