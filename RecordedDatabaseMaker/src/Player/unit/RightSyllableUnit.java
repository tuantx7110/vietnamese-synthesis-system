package Player.unit;

public class RightSyllableUnit {

    private String name;
    private String initialPhoneme;

    public RightSyllableUnit() {
        name = "";
        initialPhoneme = "";
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
        this.name = name.trim().replaceAll(" ", "_");
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
}
