import selenium
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.edge.service import Service
import time
import csv 
edge_driver_path = r'C:/Users/hp/msedgedriver.exe'

# Configure Edge options
edge_options = webdriver.EdgeOptions()
edge_options.headless = False
service = Service(executable_path=edge_driver_path)
service.start()
driver = webdriver.Edge(service=service)
driver.implicitly_wait(5)
baseUrl = "https://youtube.com/"
keyword = "Programming"

def getChannelUrl():
    driver.get(f"{baseUrl}/search?q={keyword}")
    time.sleep(3)
    
    num_scrolls = 15
    for _ in range(num_scrolls):
        driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
        time.sleep(2)
    
    allChannelList = driver.find_elements(By.CSS_SELECTOR, "#text.style-scope.ytd-channel-name a.yt-simple-endpoint.style-scope.yt-formatted-string")
    links = list(dict.fromkeys(map(lambda a: a.get_attribute("href"), allChannelList)))
    return links

def getChannelDetails(urls):
    details = []
    for url in urls:
        driver.get(f"{url}/about")
        cname = driver.find_element(By.CSS_SELECTOR, "#text.style-scope.ytd-channel-name").text
        cDess = driver.find_element(By.CSS_SELECTOR, "#description-container > yt-formatted-string:nth-child(2)").text
        clink = url
        subscriber_count_element = driver.find_element(By.CSS_SELECTOR, "#subscriber-count")
        subscriber_count = subscriber_count_element.text if subscriber_count_element else "Subscriber count not available"
        total_views_element = driver.find_element(By.XPATH, "//yt-formatted-string[contains(@class, 'style-scope ytd-channel-about-metadata-renderer') and contains(text(), 'views')]")
        total_views = total_views_element.text if total_views_element else "Total views not available"

        obj = {
            "Channel Name": cname,
            "Channel URL": clink,
            "Channel Description": cDess,
            "Subscriber Count": subscriber_count,
            "Total Views": total_views
        }
        details.append(obj)
    return details

if __name__ == "__main__":
    allChannelUrls = getChannelUrl()
    allChannelDetails = getChannelDetails(allChannelUrls)
    csv_file_path = "youtube_channel_details.csv"
    with open(csv_file_path, mode='w', newline='', encoding='utf-8') as csv_file:
        fieldnames = [
            "Channel Name",
            "Channel URL",
            "Channel Description",
            "Subscriber Count",
            "Total Views"
        ]
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        
        writer.writeheader()
        for detail in allChannelDetails:
            writer.writerow(detail)
    
    print(f"Channel details written to {csv_file_path}")
