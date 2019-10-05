# generate myls:
ls: src/source/file.cpp src/source/myls.cpp
	g++ -o bin/myls src/source/file.cpp src/source/myls.cpp -w 
cat: src/source/file.cpp src/source/mycat.cpp
	g++ -o bin/mycat src/source/file.cpp src/source/mycat.cpp -w 
cp: src/source/file.cpp src/source/mycp.cpp
	g++ -o bin/mycp src/source/file.cpp src/source/mycp.cpp -w
diff: src/source/file.cpp src/source/mydiff.cpp
	g++ -o bin/mydiff src/source/file.cpp src/source/mydiff.cpp -w
mv: src/source/file.cpp src/source/mymv.cpp
	g++ -o bin/mymv src/source/file.cpp src/source/mymv.cpp -w
rm: src/source/file.cpp src/source/myrm.cpp
	g++ -o bin/myrm src/source/file.cpp src/source/myrm.cpp -w
stat: src/source/file.cpp src/source/mystat.cpp
	g++ -o bin/mystat src/source/file.cpp src/source/mystat.cpp -w
clean:
	rm bin/*.o src/source/*.o
