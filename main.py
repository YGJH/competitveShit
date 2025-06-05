"""
自動點擊並檢查結果的爬蟲腳本
需要手動登入後，腳本會等待30秒，再開始自動化操作

請先手動運行:
  "C:\Program Files\Google\Chrome\Application\chrome.exe" --remote-debugging-port=9222
"""
import time
import os
import json
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait, Select
from selenium.webdriver.support import expected_conditions as EC
import platform

# 要操作的目標 URL
URL = 'https://etutor2.itsa.org.tw/mod/teachingzone/problem_view.php?id=36935'

# XPaths
BUTTON_XPATH = '/html/body/div[5]/div/div[2]/div[2]/div/button'
RESULT_XPATH = '/html/body/div[5]/div/div[2]/div[3]/div/div[2]/table/tbody/tr[1]/td[2]'

# configure ChromeOptions with custom user-agent
options = webdriver.ChromeOptions()
options.add_argument("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/137.0.0.0 Safari/537.36")

# init driver with options
driver = webdriver.Chrome(options=options)
driver.maximize_window()  # 全螢幕顯示

# load cookies to skip login
base_url = 'https://etutor2.itsa.org.tw/'
driver.get(base_url)
cookies_file = os.path.join(os.getcwd(), 'etutor2.itsa.org.tw_cookies.txt')
with open(cookies_file, 'r', encoding='utf-8') as f:
    for line in f:
        if line.startswith('#') or not line.strip():
            continue
        domain, flag, path, secure, expiration, name, value = line.strip().split('\t')
        cookie = {
            'domain': domain,
            'path': path,
            'secure': secure.upper() == 'TRUE',
            'name': name,
            'value': value
        }
        # only set expiry if valid non-zero expiration
        if expiration and expiration != '0':
            cookie['expiry'] = int(expiration)
        driver.add_cookie(cookie)

driver.get(URL)
# then navigate to target URL

# 給予人工登入時間，可選
# print("請在30秒內完成登入...")
# time.sleep(10)
# print("開始自動檢查前先選擇編譯選項...")

# 選擇 C++ 選項
select1 = Select(driver.find_element(By.XPATH, '/html/body/div[5]/div/div[2]/div[2]/div/select[1]'))
select1.select_by_visible_text('C++')
# 選擇版本 9.0.1
select2 = Select(driver.find_element(By.XPATH, '/html/body/div[5]/div/div[2]/div[2]/div/select[2]'))
select2.select_by_visible_text('9.0.1')
# 選擇標準 c++2a
select3 = Select(driver.find_element(By.XPATH, '/html/body/div[5]/div/div[2]/div[2]/div/select[3]'))
select3.select_by_visible_text('c++2a')

print("開始自動檢查...")

try:
    # 先點一次按鈕
    driver.find_element(By.XPATH, BUTTON_XPATH).click()
    while True:
        # 等待結果出現「錯誤結果」或「完全正確」其中之一
        WebDriverWait(driver, 120).until(
            lambda d: d.find_element(By.XPATH, RESULT_XPATH).text in ["錯誤結果", "完全正確"]
        )
        result_text = driver.find_element(By.XPATH, RESULT_XPATH).text
        print(f"目前結果：{result_text}")

        if result_text == "完全正確":
            print("得到完全正確，停止腳本。")
            break
        else:
            print("結果為錯誤，重新點擊按鈕...")
            driver.find_element(By.XPATH, BUTTON_XPATH).click()
            # 可適度等待
            time.sleep(2)
finally:
    driver.quit()
