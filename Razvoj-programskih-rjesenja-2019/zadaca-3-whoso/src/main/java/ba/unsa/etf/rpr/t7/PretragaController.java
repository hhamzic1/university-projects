package ba.unsa.etf.rpr.t7;

import at.mukprojects.giphy4j.Giphy;
import at.mukprojects.giphy4j.entity.giphy.GiphyData;
import at.mukprojects.giphy4j.entity.giphy.GiphyImage;
import at.mukprojects.giphy4j.entity.search.SearchFeed;
import at.mukprojects.giphy4j.exception.GiphyException;
import com.lowagie.text.pdf.codec.GifImage;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


import javax.swing.*;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;


public class PretragaController implements Initializable {

    public TextField fldPretraga;
    public Button btnPretraga;
    public Button btnOk;
    public Button btnCancel;
    public ScrollPane skrolPejn;
    public String izabranaSlika;
    public TilePane tajlPejn;
    public boolean okPritisnuto;
    public boolean cancelPritisnuto;

    public PretragaController() {
    }


    public void okAction(ActionEvent event){
        if(fldPretraga.getText().equals("") || izabranaSlika==null){
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Nijedna slika nije izabrana");
            alert.setHeaderText("Niste izabrali sliku koju želite");
            alert.setContentText("Unesite pretragu a zatim izaberite sliku, i pritisnite Ok");
            alert.showAndWait();
        }
        else{
            okPritisnuto=true;
            Stage prozor = (Stage) skrolPejn.getScene().getWindow();
            prozor.close();
        }
    }

    public void cancelAction(ActionEvent event){
        this.cancelPritisnuto=true;
        Stage prozor = (Stage) skrolPejn.getScene().getWindow();
        prozor.close();
    }


    public void pretragaAction() throws InterruptedException {
        tajlPejn.getChildren().clear();
        if(fldPretraga.getText()!=null) {
            Giphy giphy = new Giphy("dc6zaTOxFJmzC");
            List<String> urls = new ArrayList<>();
            Thread thread = null;
            Task<Boolean> zadatak = null;

            for (int i = 0; i < 25; i++) {
                Button tempDugme = new Button();
                Image img = new Image("/slike/loading.gif");
                ImageView imVju = new ImageView(img);
                imVju.setFitHeight(128);
                imVju.setFitWidth(128);
                tempDugme.setGraphic(imVju);
                tajlPejn.getChildren().add(tempDugme);

                int finalI = i;
                zadatak = new Task<Boolean>() {
                    @Override
                    protected Boolean call() throws Exception {
                        SearchFeed feed = null;
                        try {
                            feed = giphy.searchSticker(fldPretraga.getText(), 25, 0);
                            GiphyImage g = feed.getDataList().get(finalI).getImages().getFixedWidthStill();
                            String s = g.getUrl();
                            s = s.substring(25, s.length());
                            s = "https://i.giphy.com/" + s.replaceAll("[?].*", "");
                            imVju.setImage(new Image(s));
                            tempDugme.setGraphic(imVju);
                            tempDugme.setOnAction(actionEvent -> {
                                ImageView imageVjuTemp = (ImageView) tempDugme.getGraphic();
                                izabranaSlika = imageVjuTemp.getImage().getUrl();
                            });

                            return true;
                        } catch (Exception e) {
                            e.printStackTrace();
                            return false;
                        }

                    }
                };

                thread = new Thread(zadatak);
                thread.start();

            }
        }

    }


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        skrolPejn.setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        skrolPejn.setVbarPolicy(ScrollPane.ScrollBarPolicy.AS_NEEDED);
        skrolPejn.setFitToHeight(true);
        skrolPejn.setFitToWidth(true);
        skrolPejn.setContent(tajlPejn);

    }

    public String getPutanjaSlike()
    {
        return this.izabranaSlika;
    }

    public boolean isOkPritisnuto(){
        if(okPritisnuto) return true;
        return false;
    }
    public boolean isCancelPritisnuto(){
        if(cancelPritisnuto) return true;
        return false;
    }
}
