import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.SecureRandom;
import java.security.spec.KeySpec;
import java.util.Base64;
import java.io.UnsupportedEncodingException;
public class AES256 {
  private static final int KEY_LENGTH = 256;
  private static final int ITERATION_COUNT = 65536;
  public static String decrypt(String strToDecrypt, String secretKey, String salt) {
    try {
        byte[] encryptedData = Base64.getDecoder().decode(strToDecrypt);
        byte[] iv = new byte[16];
        System.arraycopy(encryptedData, 0, iv, 0, iv.length);
        IvParameterSpec ivspec = new IvParameterSpec(iv);
        SecretKeyFactory factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA256");
        KeySpec spec = new PBEKeySpec(secretKey.toCharArray(), salt.getBytes(), ITERATION_COUNT, KEY_LENGTH);
        SecretKey tmp = factory.generateSecret(spec);
        SecretKeySpec secretKeySpec = new SecretKeySpec(tmp.getEncoded(), "AES");
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec, ivspec);
        byte[] cipherText = new byte[encryptedData.length - 16];
        System.arraycopy(encryptedData, 16, cipherText, 0, cipherText.length);
        byte[] decryptedText = cipher.doFinal(cipherText);
        return new String(decryptedText, "UTF-8");
    } catch (Exception e) {
        // Handle the exception properly
        e.printStackTrace();
        return null;
    }
  }
  public static void main(String[] args) {

    // Define your secret key and salt (keep these secure and don't hardcode in production)
    String secretKey = "";
    String salt = "";

    // String to be encrypted
    String originalString = "Hello, this is a secret message.";

    // Encrypt the string

    // Decrypt the string
    String decryptedString = AES256.decrypt("cbecf066b001773aee66337b142a2163c51103ff90d8ada936b99066a88fc5cf", secretKey, salt);
    if (decryptedString != null) {
        System.out.println("Decrypted: " + decryptedString);
    } else {
        System.err.println("Decryption failed.");
    }
  }
}
