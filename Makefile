



TARGETDIR	:=build/
GCOMPILER :=g++
GCOMPILER_gcc :=gcc
FILECLASS_DEFINITION :=-D _x86_COMPILE



OBJECTS	:=$(addprefix $(TARGETDIR), TestProjectMain.o OrderBook.o OrderList.o OrderBaseList.o Parser.o)


LIBS	:= -lpthread -luuid -lz -lm -lpthread -pthread -ldl

CFLAGS =-I -I/usr/include -g

$(TARGETDIR)orderbook: $(OBJECTS)
	$(GCOMPILER) $(CFLAGS) -o $(TARGETDIR)orderbook $(OBJECTS)

$(TARGETDIR)TestProjectMain.o: TestProjectMain.cpp
	$(GCOMPILER) $(CFLAGS) -c TestProjectMain.cpp -o $(TARGETDIR)TestProjectMain.o

$(TARGETDIR)OrderBook.o: OrderBook.cpp
	$(GCOMPILER) $(CFLAGS) -c OrderBook.cpp -o $(TARGETDIR)OrderBook.o

$(TARGETDIR)OrderList.o: OrderList.cpp
	$(GCOMPILER) $(CFLAGS) -c OrderList.cpp -o $(TARGETDIR)OrderList.o

$(TARGETDIR)OrderBaseList.o: OrderBaseList.cpp
	$(GCOMPILER) $(CFLAGS) -c OrderBaseList.cpp -o $(TARGETDIR)OrderBaseList.o

$(TARGETDIR)Parser.o: Parser.cpp
	$(GCOMPILER) $(CFLAGS) -c Parser.cpp -o $(TARGETDIR)Parser.o
clean:
	rm $(TARGETDIR)*.o
	rm $(TARGETDIR)orderbook

