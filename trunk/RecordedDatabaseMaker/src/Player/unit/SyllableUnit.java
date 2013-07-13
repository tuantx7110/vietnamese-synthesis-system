package Player.unit;

public class SyllableUnit {

    private int id;
    private String name;
    private int startIndex;
    private int endIndex;
    private String initialPhoneme;
    private String finalPhoneme;
    private LeftSyllableUnit leftSyllable;
    private RightSyllableUnit rightSyllable;

    public SyllableUnit() {
        id = -1;
        name = "";
        startIndex = -1;
        endIndex = -1;
        initialPhoneme = "";
        finalPhoneme = "";
        leftSyllable = new LeftSyllableUnit();
        rightSyllable = new RightSyllableUnit();
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
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name.trim().replaceAll(" ", "_").toLowerCase();
    }

    /**
     * @return the startIndex
     */
    public int getStartIndex() {
        return startIndex;
    }

    /**
     * @param startIndex the startIndex to set
     */
    public void setStartIndex(int startIndex) {
        this.startIndex = startIndex;
    }

    /**
     * @return the endIndex
     */
    public int getEndIndex() {
        return endIndex;
    }

    /**
     * @param endIndex the endIndex to set
     */
    public void setEndIndex(int endIndex) {
        this.endIndex = endIndex;
    }

    /**
     * @return the initialPhoneme
     */
    public String getInitialPhoneme() {
        return initialPhoneme;
    }

    /**
     * @param initialPhoneme the initialPhoneme to set
     */
    public void setInitialPhoneme(String initialPhoneme) {
        this.initialPhoneme = initialPhoneme;
    }

    /**
     * @return the finalPhoneme
     */
    public String getFinalPhoneme() {
        return finalPhoneme;
    }

    /**
     * @param finalPhoneme the finalPhoneme to set
     */
    public void setFinalPhoneme(String finalPhoneme) {
        this.finalPhoneme = finalPhoneme;
    }

    /**
     * @return the leftSyllable
     */
    public LeftSyllableUnit getLeftSyllable() {
        return leftSyllable;
    }

    /**
     * @param leftSyllable the leftSyllable to set
     */
    public void setLeftSyllable(LeftSyllableUnit leftSyllable) {
        this.leftSyllable = leftSyllable;
    }

    /**
     * @return the rightSyllable
     */
    public RightSyllableUnit getRightSyllable() {
        return rightSyllable;
    }

    /**
     * @param rightSyllable the rightSyllable to set
     */
    public void setRightSyllable(RightSyllableUnit rightSyllable) {
        this.rightSyllable = rightSyllable;
    }
}
