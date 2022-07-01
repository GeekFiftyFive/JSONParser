ARGS = -std=c99 -Wall -O2 -g -D_DEFAULT_SOURCE=__STRICT_ANSI__

MKDIR = mkdir -p

OBJ_DIR = obj

.PHONY: objDir

all: objDir jsonParser

objDir:
	${MKDIR} ${OBJ_DIR}

jsonParser: obj/main.o\
							obj/hashMap.o\
							obj/linkedList.o\
							obj/tuple.o\
							obj/fileIO.o\
							obj/logger.o\
							obj/jsonCore.o\
							obj/jsonParser.o\
							obj/stringUtils.o
								cc $(ARGS) -o jsonParser obj/main.o\
									obj/hashMap.o\
									obj/linkedList.o\
									obj/tuple.o\
									obj/fileIO.o\
									obj/logger.o\
									obj/jsonCore.o\
									obj/jsonParser.o\
									obj/stringUtils.o

obj/main.o: src/main.c
			cc $(ARGS) -c src/main.c -o obj/main.o

obj/hashMap.o: src/DataStructures/HashMap/hashMap.c src/DataStructures/HashMap/hashMap.h
			cc $(ARGS) -c src/DataStructures/HashMap/hashMap.c -o obj/hashMap.o

obj/linkedList.o: src/DataStructures/LinkedList/linkedList.c src/DataStructures/LinkedList/linkedList.h
			cc $(ARGS) -c src/DataStructures/LinkedList/linkedList.c -o obj/linkedList.o

obj/fileIO.o: src/IO/fileIO.c src/IO/fileIO.h
			cc $(ARGS) -c src/IO/fileIO.c -o obj/fileIO.o

obj/logger.o: src/IO/logger.c src/IO/logger.h
			cc $(ARGS) -c src/IO/logger.c -o obj/logger.o

obj/jsonParser.o: src/JSON/jsonParser.c src/JSON/jsonParser.h
			cc $(ARGS) -c src/JSON/jsonParser.c -o obj/jsonParser.o

obj/tuple.o: src/DataStructures/Tuple/tuple.c src/DataStructures/Tuple/tuple.h
			cc $(ARGS) -c src/DataStructures/Tuple/tuple.c -o obj/tuple.o

obj/stringUtils.o: src/Utils/stringUtils.c src/Utils/stringUtils.h
			cc $(ARGS) -c src/Utils/stringUtils.c -o obj/stringUtils.o

obj/jsonCore.o: src/JSON/jsonCore.c src/JSON/jsonCore.h
			cc $(ARGS) -c src/JSON/jsonCore.c -o obj/jsonCore.o

clean:
	rm -rf obj/* && rm jsonParser
