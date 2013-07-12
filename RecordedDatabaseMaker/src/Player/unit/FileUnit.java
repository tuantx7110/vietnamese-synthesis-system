package Player.unit;

import java.util.ArrayList;
import java.util.List;

public class FileUnit {

    private String filename;
    private List<SentenceUnit> sentences;

    public FileUnit() {
        filename = "";
        sentences = new ArrayList<SentenceUnit>();
    }

    public void addSentence(SentenceUnit sentence) {
        getSentences().add(sentence);
    }

    /**
     * @return the filename
     */
    public String getFilename() {
        return filename;
    }

    /**
     * @param filename the filename to set
     */
    public void setFilename(String filename) {
        this.filename = filename;
    }

    /**
     * @return the sentences
     */
    public List<SentenceUnit> getSentences() {
        return sentences;
    }

    /**
     * @param sentences the sentences to set
     */
    public void setSentences(List<SentenceUnit> sentences) {
        this.sentences = sentences;
    }
}
