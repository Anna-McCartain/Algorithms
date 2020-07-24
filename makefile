CFLAGS=-g -Wall -std=c99
LDFLAGS=-lm
CC=gcc

# "make darray", "make bstree" or "make hash" to compile your code

darray:
	$(CC) $(CFLAGS) -DDARRAY $(LDFLAGS) global.c speller.c darray.c sorting.c -o speller_darray

bstree:
	$(CC) $(CFLAGS) -DBSTREE $(LDFLAGS) global.c speller.c bstree.c -o speller_bstree

hash:
	$(CC) $(CFLAGS) -DHASH $(LDFLAGS) global.c speller.c hashset.c -o speller_hash


tidy:
	-rm *.o speller_darray speller_bstree speller_hash

.PHONY: darray bstree hash

################################################################################
# Comment out the next line once you have debugged your code
# RUN=valgrind
# Uncomment the next line to time your code (instead of using valgrind)
RUN=time
# If you comment out both RUNs above you can run your program by itself

# to test: e.g. "make testdarray"

MODE=-m 2

testdarray: darray
	# @echo "10"
	# $(RUN) ./speller_darray -d data/10_word -vvv $(MODE) data/find_front
	# @echo "100"
	# $(RUN) ./speller_darray -d data/100_words -vvv $(MODE) data/find
	@echo "1000"
	$(RUN) ./speller_darray -d data/1k_words -vvv $(MODE) data/find
	# @echo "1000"
	# $(RUN) ./speller_darray -d data/1k_sorted -vvv $(MODE) data/find_quarter
	# @echo "1000"
	# $(RUN) ./speller_darray -d data/1k_sorted -vvv $(MODE) data/find_middle
	# @echo "1000"
	# $(RUN) ./speller_darray -d data/1k_sorted -vvv $(MODE) data/find_back
	# @echo "10000"
	# $(RUN) ./speller_darray -d data/10k_sorted -vvv $(MODE) data/find_front
	# # @echo "1000 sort"
  # $(RUN) ./speller_darray -d data/1k_sorted -vvv $(MODE) data/find_front
# small dictionaries that give trees that are unbalanced in various ways
testtree: bstree
	#$(RUN) ./speller_bstree -d data/10_word $(MODE) -vvv data/find
	#$(RUN) ./speller_bstree -d data/100_words $(MODE) -vvv data/find
	#$(RUN) ./speller_bstree -d data/1k_words $(MODE) -vvv data/find
	$(RUN) ./speller_bstree -d data/10k_word $(MODE) -vvv data/find
	#@echo
	#$(RUN) ./speller_bstree -d data/sample-dictionary $(MODE) -vv data/sample-file

testhash: hash
	# $(RUN) ./speller_hash -d data/sample-dictionary -s 13 $(MODE) -vv data/sample-file
	# @echo "This mightd fail as the dictionary is bigger than the hashtable"
	# $(RUN) ./speller_hash -d data/sample-dictionary -s 5 $(MODE) -vvv data/sample-file

	#$(RUN) ./speller_bstree -d data/10_word $(MODE) -vvv data/find
	#$(RUN) ./speller_bstree -d data/100_words $(MODE) -vvv data/find
	$(RUN) ./speller_bstree -d data/1k_words $(MODE) -vvv data/find
	#$(RUN) ./speller_bstree -d data/10k_word $(MODE) -vvv data/find
