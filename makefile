GPP=g++
PROJ_FILES_PATH=.
TESTS_DIR=./UnitTests
O_FILES_DIR=$(TESTS_DIR)/OFiles
EXEC=WorldCupUnitTester
TESTS_INCLUDED_FILE=worldcup23a2.h $(TESTS_DIR)/catch.hpp

OBJS=$(O_FILES_DIR)/UnitTests.o $(O_FILES_DIR)/Team.o $(O_FILES_DIR)/Player.o $(O_FILES_DIR)/worldcup23a2.o $(O_FILES_DIR)/Tuple.o  $(O_FILES_DIR)/UnionFind.o $(O_FILES_DIR)/PlayerNode.o # UPDATE HERE ALL THE O FILES YOU CREATED BELOW

DEBUG_FLAG= -g # can add -g
COMP_FLAG=--std=c++11 -Wall -Werror -pedantic-errors $(DEBUG_FLAG)

$(EXEC) : $(OBJS)
	$(GPP) $(COMP_FLAG) $(OBJS) -o $@

$(O_FILES_DIR)/UnitTests.o : $(TESTS_DIR)/UnitTests.cpp
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) $(TESTS_DIR)/UnitTests.cpp -o $@

 # UPDATE FROM HERE
	
$(O_FILES_DIR)/Tuple.o : Tuple.cpp Tuple.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Tuple.cpp -o $@
	
$(O_FILES_DIR)/Team.o : Team.cpp Team.h Player.h AVLTree.h Tuple.h Exception.h UnionFind.h PlayerNode.h wet2util.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Team.cpp -o $@

$(O_FILES_DIR)/Player.o : Player.cpp Player.h AVLTree.h Team.h Pair.h Tuple.h Exception.h PlayerNode.h wet2util.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) Player.cpp -o $@

$(O_FILES_DIR)/worldcup23a2.o : worldcup23a2.cpp worldcup23a2.h wet2util.h AVLTree.h Team.h Player.h Tuple.h Pair.h Exception.h UnionFind.h RankTree.h PlayerNode.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) worldcup23a2.cpp -o $@

$(O_FILES_DIR)/UnionFind.o : UnionFind.cpp UnionFind.h wet2util.h Player.h Team.h HashTable.h PlayerNode.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) UnionFind.cpp -o $@

$(O_FILES_DIR)/PlayerNode.o : PlayerNode.cpp PlayerNode.h Player.h Team.h wet2util.h UnionFind.h
	@mkdir -p $(O_FILES_DIR)
	$(GPP) -c $(COMP_FLAG) PlayerNode.cpp -o $@

 # UNTIL HERE

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
