package Player;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class TextFile {

    private Scanner scanner;
    private File textFile;
    private String content;

    public TextFile(File textFile) throws FileNotFoundException {
        this.textFile = textFile;
        scanner = new Scanner(textFile);
    }

    public void readAll() {
        StringBuilder builder = new StringBuilder();
        while (scanner.hasNext()) {
            String s = scanner.next();
            builder.append(" ").append(s);
        }
        content = builder.toString().trim();
    }

    public String getContent() {
        return content;
    }
}
