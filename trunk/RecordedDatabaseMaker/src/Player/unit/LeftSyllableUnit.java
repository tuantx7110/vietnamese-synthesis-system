package Player.unit;

public class LeftSyllableUnit {

    private String name;
    private String finalPhoneme;

    public LeftSyllableUnit() {
        name = "";
        finalPhoneme = "";
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
}
