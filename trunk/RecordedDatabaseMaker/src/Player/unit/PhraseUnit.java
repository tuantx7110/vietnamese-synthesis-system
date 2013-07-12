package Player.unit;

import java.util.ArrayList;
import java.util.List;

public class PhraseUnit {

    private int id;
    private int length;
    private List<SyllableUnit> syllables;

    public PhraseUnit() {
        id = -1;
        length = -1;
        syllables = new ArrayList<SyllableUnit>();
    }

    public void addSyllable(SyllableUnit syllable) {
        syllables.add(syllable);
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the length
     */
    public int getLength() {
        return length;
    }

    /**
     * @param length the length to set
     */
    public void setLength(int length) {
        this.length = length;
    }

    /**
     * @return the syllables
     */
    public List<SyllableUnit> getSyllables() {
        return syllables;
    }

    /**
     * @param syllables the syllables to set
     */
    public void setSyllables(List<SyllableUnit> syllables) {
        this.syllables = syllables;
    }
}
