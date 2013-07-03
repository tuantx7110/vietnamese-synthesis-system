package Player;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class TextFile {

    private Scanner scanner;
    private File textFile;
    private String content;

    public TextFile(File textFile) throws FileNotFoundException {
        this.textFile = textFile;
        scanner = new Scanner(textFile, "UTF-8");
    }

    public void readAll() {
        StringBuilder builder = new StringBuilder();
        while (scanner.hasNext()) {
            String s = scanner.next();
            List<String> a = parse(s);
            for (int i = 0; i < a.size(); ++i) {
                builder.append(a.get(i).trim()).append(' ');
            }
        }
        content = builder.toString().trim();
    }

    private List<String> parse(String s) {
        s = s.trim() + " ";

        List<String> result = new ArrayList<String>();

        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < s.length(); ++i) {
            char c = s.charAt(i);
            if (Character.isLetterOrDigit(c)) {
                builder.append(c);
            } else {
                if (builder.length() > 0) {
                    result.add(builder.toString().trim().toLowerCase());
                }
                if (!Character.isSpaceChar(c)) {
                    String a = "" + c;
                    result.add(a.trim().toLowerCase());
                }
                builder = new StringBuilder();
            }
        }

        return result;
    }

    public String getContent() {
        return content;
    }
}
