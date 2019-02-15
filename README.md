# 綠界物流Drupal Commerce Shipping 模組

這個模組主要是整合**綠界科技**的[物流服務](https://www.ecpay.com.tw/IntroTransport)，目前模組內的SDK已經更新至版本**1.0.181221**。這個模組由於一開始並非以要開源為導向，所以寫的方式沒有這麼的完善，若有任何問題歡迎PR給我。

## 簡介
這個模組主要是整合Drupal Commerce與Drupal Commerce Shipping模組，並不適用於Ubercart模組，有提供後台與權限可以來進行物流系統狀態的控制，並且有提供子模組來建立物流的Profile，方便建立與紀錄所有物流資訊。

適用版本
* Drupal 7
* Drupal Commerce
* Drupal Commerce Shipping


提供物流服務
* 超商取貨：全家便利商店
* 超商取貨：統一超商
* 超商取貨：萊爾富
* 宅配：黑貓宅急便
* 宅配：宅配通

## 後台設定
![](https://i.imgur.com/PeGNV58.png)

1. 路徑：admin/commerce/config/allpay_shipping
2. 需要搭配權限才能進行控制，user 1 可以直接更新
3. 預設的值都是測試環境的參數，改成正式環境後，務必搭配正式環境的MerchantID、HashKey、HashIV等資訊，ECPay的SDK偵測若MerchantID為測試環境的值，直接會視為測試環境。


## 物流Profile
這裡提供一個子模組**Commerce ECPay Shipping Profile**，啟用這個模組後，會立即建立一個Customer Profile，可以用來存取對應的物流紀錄。

![](https://i.imgur.com/Ep4OTQY.png)


### 備註
由於有些欄位並非要給客人所使用，而是讓物流回傳資料時紀錄使用，因此建議搭配[Conditional Field](https://www.drupal.org/project/conditional_fields)，或自行寫hook_form_alter、theme_form 來隱藏。


## 購物流程
![](https://i.imgur.com/DHfA74I.png)

在物流的Pane裡面可以選擇對應的物流方法，若正式環境，則是直接導入到電子地圖，進行後續的選擇，若在測試環境，則是直接到綠界的測試頁面，並不會產生對應的電子地圖供修正。

![](https://i.imgur.com/p56uZqv.png)

完成後，會將資料回傳，並且寫回customer profile，並且進入review頁面

![](https://i.imgur.com/w0DkIrE.png)


## 小記
目前這個模組有採用全新的Drupal來測試，並且可以實際運行。若有不足的地方，再麻煩告知或提供PR來供修正。

目前測試的版本為

Drupal：7.64
Commerce： 7.x-1.14
Shipping： 7.x-2.3