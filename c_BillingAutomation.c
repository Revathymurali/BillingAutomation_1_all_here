c_BillingAutomation_10


package automation;
import java.net.MalformedURLException; 
import java.net.URL; 
import java.util.List; 
import java.util.Set; 
import org.openqa.selenium.Keys; 
import org.openqa.selenium.StaleElementReferenceException; 
import org.openqa.selenium.By; 
import org.openqa.selenium.WebElement; 
import org.openqa.selenium.remote.DesiredCapabilities; 
import org.openqa.selenium.support.ui.ExpectedConditions; 
import org.openqa.selenium.support.ui.WebDriverWait; 
import java.time.Duration;

import io.appium.java_client.MobileBy;
import io.appium.java_client.windows.WindowsDriver; 
import io.appium.java_client.windows.WindowsElement;
public class B2CBillingTest10 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {

            // Set application path
			DesiredCapabilities cap = new DesiredCapabilities();
			// Give the billing app 5 seconds to fully load before WinAppDriver looks for the window
			cap.setCapability("ms:waitForAppLaunch", 20);
			cap.setCapability("platformName", "Windows");
			cap.setCapability("deviceName", "WindowsPC");
			cap.setCapability("app","C:\\Program Files (x86)\\Codeingz\\DevIhdbWarehouse\\billerz.ihdb.warehouse.exe");
            
            WindowsDriver driver = new WindowsDriver(
                    new URL("http://127.0.0.1:4723"),
                    cap);

            System.out.println("Application Launched Successfully!");
         // Wait
            WebDriverWait wait = new WebDriverWait(driver, 10);

            WebElement username =
                    driver.findElementByAccessibilityId("_txtUserName");

        
            username.click();          // give focus
            Thread.sleep(1000);

            username.clear();          // optional
            username.sendKeys("BIJU");
            WebElement password =
                    driver.findElementByAccessibilityId("_txtPassword"); // check in Inspect

            password.click();
            password.clear();
            password.sendKeys("abijus1");
            WebElement loginBtn =
                    driver.findElementByAccessibilityId("_btnLogin"); // check in Inspect

            loginBtn.click();

            System.out.println("Login Clicked!");
            

            Thread.sleep(3000);

            Set<String> windows = driver.getWindowHandles();
            for (String w : windows) {
                driver.switchTo().window(w);
                String title = driver.findElementByAccessibilityId("TitleBar").getAttribute("Value.Value");
                if (title.contains("Warehouse Module")) {
                    System.out.println("Main screen is open: " + title);
                 // After switching to main window
                    WindowsElement billingMenu = (WindowsElement) driver.findElementByName("BILLING");
                    billingMenu.click();
                    System.out.println("Billing menu clicked!");
                    WindowsElement wholesaleBilling = (WindowsElement) driver.findElementByName("Credit Billing [B2C]");
                    wholesaleBilling.click();
                    System.out.println("Wholesale Billing B2C clicked!");
                    Thread.sleep(15000);
                    WindowsElement customerName = (WindowsElement) driver.findElementByAccessibilityId("_textBoxPatientName");
                    customerName.click();
                    customerName.clear();
                    customerName.sendKeys("C-ASRAYA RCC");
                    customerName.sendKeys(Keys.ENTER);   // press ENTER after typing
                    WindowsElement pickedBy = (WindowsElement) driver.findElementByAccessibilityId("_txtPickBy");
                    pickedBy.click();
                    pickedBy.clear();
                    pickedBy.sendKeys("ADYA-112");
                    pickedBy.sendKeys(Keys.ENTER);   // press ENTER
                    System.out.println("Picked By field edited!");
                    Thread.sleep(2000);  // wait 2 seconds (adjust if needed)

                 // click the Yes button
                 WindowsElement yesButton = (WindowsElement) driver.findElementByName("Yes");
                 yesButton.click();

                 System.out.println("Yes button clicked!");
                    WindowsElement checkBy = (WindowsElement) driver.findElementByAccessibilityId("_txtCheckBy");
                    checkBy.click();
                    checkBy.clear();
                    checkBy.sendKeys("ADYA-112");
                    checkBy.sendKeys(Keys.ENTER);   // press ENTER
                    System.out.println("Check By field edited!");
                    Thread.sleep(2000);
                    List<WindowsElement> yesButtons = driver.findElementsByName("Yes");
                    yesButtons.get(yesButtons.size() - 1).click();  // clicks the last Yes button

                 System.out.println("Yes button clicked!");
              // wait a bit if needed
                 Thread.sleep(10000);

                 // find the Product Name field by AutomationId
                 WindowsElement productNameField = (WindowsElement) driver.findElementByAccessibilityId("_textBoxPrdt");

                 // click to focus (optional but good)
                 productNameField.click();

                 
              // list of first 10 products from dropdown
                 String[] products = {
                         "2",
                         "24 k TAB",
                         "3 LUMEN EXTRACTION",
                         "3 WAY",
                         "5 FLURO URACIL 250",
                         "5 FLURO URACIL 500",
                         "6 MP",
                         "6 TG",
                         "A  TO  Z NS  DROPS",
                         "A  TO  Z NS  SYP"
                 };

                 for (String product : products) {

                	    // Enter product name
                	    productNameField.click();
                	    productNameField.sendKeys(Keys.CONTROL + "a");
                	    productNameField.sendKeys(Keys.DELETE);
                	    productNameField.sendKeys(product);
                	    Thread.sleep(1000);
                	    productNameField.sendKeys(Keys.ARROW_DOWN);
                	    Thread.sleep(300);
                	    productNameField.sendKeys(Keys.ENTER);

                	    System.out.println("Product selected: " + product);

                	    // wait for UI update
                	    Thread.sleep(12000);

                	    int qty = 0;

                	    try {

                	    	WindowsElement availQtyPane =
                	    	        (WindowsElement) driver.findElementByAccessibilityId("labelX17");

                	    	String qtyText = availQtyPane.getAttribute("Value.Value");

                	    	if (qtyText == null || qtyText.trim().isEmpty()) {
                	    	    qtyText = availQtyPane.getText();
                	    	}

                	    	System.out.println("Raw Qty Text: " + qtyText);

                	    	if (qtyText != null) {
                	    	    qtyText = qtyText.replaceAll("[^0-9]", "").trim();
                	    	    if (!qtyText.isEmpty()) {
                	    	        qty = Integer.parseInt(qtyText);
                	    	    }
                	    	}

                	    	

                	        

                	    } catch (Exception e) {
                	        System.out.println("Qty read error for " + product);
                	    }

                	    System.out.println("Available Qty for " + product + ": " + qty);

                	    if (qty > 0) {

                	    	WebDriverWait wait1 = new WebDriverWait(driver, 10); // 10 seconds
                	    	WindowsElement qtyField = (WindowsElement) wait.until(
                	    	        ExpectedConditions.elementToBeClickable(MobileBy.AccessibilityId("_textBoxQty"))
                	    	);
                	    	qtyField.clear();
                	    	qtyField.sendKeys("2");
                	    	qtyField.sendKeys(Keys.ENTER);

                	    	System.out.println("Qty 2 entered for " + product);

                	    } else {

                	        System.out.println("Skipping: " + product + " (Qty is zero)");

                	    }

                	    Thread.sleep(1500);
                	}
                   
                 // Wait a little if screen is loading
                    Thread.sleep(2000);

                    // Find Bill Now button using AutomationId
                    WindowsElement billNowButton = (WindowsElement) driver.findElementByAccessibilityId("_buttonSave");

                    // Click the button
                    billNowButton.click();

                    System.out.println("Bill Now button clicked successfully!");
                 // 1. Wait for the confirmation box to appear
                    WebDriverWait waitConfirm = new WebDriverWait(driver, 5);

                    try {
                        // 2. Locate the "Yes" button by Name and click it
                        WindowsElement confirmYes = (WindowsElement) waitConfirm.until(
                            ExpectedConditions.elementToBeClickable(By.name("Yes"))
                        );
                        
                        confirmYes.click();
                        System.out.println("Confirmation 'Yes' clicked successfully!");

                    } catch (Exception e) {
                        // 3. Fallback: If standard click fails, try pressing the 'Y' key (common shortcut for Yes)
                        System.out.println("Button not found by name, attempting Keyboard Shortcut 'Alt+Y'");
                        driver.getKeyboard().sendKeys("y"); 
                    }
                    Thread.sleep(20000);
                    driver.getKeyboard().sendKeys(Keys.ENTER);
                    System.out.println("Enter key sent to confirmation box!");
                    WebDriverWait waitClose = new WebDriverWait(driver, 15);

                    WindowsElement closeButton = (WindowsElement) waitClose.until(
                            ExpectedConditions.elementToBeClickable(By.name("Close"))
                    );

                    closeButton.click();

                    System.out.println("Close button clicked successfully!");
                    break;
                }
            }
            
           
        } catch (Exception e) {
            e.printStackTrace();
        }
			
		
		}

}
