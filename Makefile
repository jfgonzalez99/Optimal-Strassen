all:
	javac src/Strassen.java && javac src/Matrix.java && chmod +x strassen

clean:
	rm -f src/Strassen.class && rm -f src/Matrix.class
