preprocess: preprocess.c++
	g++ -o preprocess preprocess.c++
	./preprocess <test.txt > pre-file.txt