all:
	javac src/Driver.java && chmod +x strassen

clean:
	rm -f src/Driver.class