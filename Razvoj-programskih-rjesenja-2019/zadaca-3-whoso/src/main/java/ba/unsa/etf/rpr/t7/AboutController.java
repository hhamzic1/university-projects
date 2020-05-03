package ba.unsa.etf.rpr.t7;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import java.net.URL;
import java.util.ResourceBundle;

public class AboutController implements Initializable {
    @FXML
    ImageView imgVju;

    public AboutController(){
    }


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        Image img = new Image("/slike/starimost.jpg");
        imgVju.setImage(img);
    }
}
