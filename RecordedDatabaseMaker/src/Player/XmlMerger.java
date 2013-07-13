package Player;

import Player.unit.FileUnit;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

public class XmlMerger {

    private File[] xmlFiles;
    private File outputFile;
    private File statisticFile;
    private File dictionaryFile;

    public XmlMerger(File[] xmlFiles, String outputFolder) {
        this.xmlFiles = xmlFiles;
        this.outputFile = new File(outputFolder + "/recorded_database_description.xml");
        this.statisticFile = new File(outputFolder + "/statistic.txt");
        this.dictionaryFile = new File(outputFolder + "/compound_dictionary.txt");
    }

    public String start() throws Exception {
        XmlDatabaseWriter writer = new XmlDatabaseWriter(outputFile);
        DatabaseStatistic statistic = new DatabaseStatistic();

        writer.open();

        for (int i = 0; i < xmlFiles.length; ++i) {
            XmlDatabaseReader reader = new XmlDatabaseReader(xmlFiles[i]);
            FileUnit fileUnit = reader.loadData();
            writer.writeFileUnit(fileUnit);
            statistic.addFileUnit(fileUnit);
        }

        writer.close();

        statistic.writeStatisticFile(statisticFile);
        statistic.writeCompoundDictionary(dictionaryFile);

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream out = new PrintStream(baos);
        statistic.display(out, false);

        return baos.toString();
    }
}
