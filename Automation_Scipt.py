from ftplib import FTP
import sys
import csv
import pandas as pd
import numpy as np
import re
from selenium import webdriver
from selenium.webdriver import Firefox
from selenium.webdriver import Firefox
from time import sleep
from selenium.webdriver.common import keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from sys import argv
import datetime
from dateutil.relativedelta import relativedelta
import glob
import pandas as pd
import os
import shutil

########################################Selecting Template and setting prelimnary variables
Org="WALLMART"
profile = "Loyalty"
url = "abcd.com"
user = "xyz"
pass = "xyz"
xyz="org_selection_dropdown"
tomorrow = datetime.datetime.now()+relativedelta(days=1)
now = datetime.datetime.now()
previous_day=datetime.datetime.now()-relativedelta(days=1)
start_year=previous_day.year
start_month=previous_day.strftime("%b")
start_day=previous_day.day

end_year=tomorrow.year
end_month=tomorrow.strftime("%b")
end_day=tomorrow.day

raw_input_files='C:\\Python27\\Raw_Error_Files\\'
processed_files='C:\\Python27\\Processed_files\\'
ftp_files='C:\\Python27\\ftp_files\\'
    
num=0


########################################Starting Instance of Chrome.
chromeOptions = webdriver.ChromeOptions()
prefs = {"download.default_directory" : raw_input_files}
chromeOptions.add_experimental_option("prefs",prefs)
f = webdriver.Chrome(executable_path='C:\.........\chromedriver_win32\chromedriver.exe',chrome_options=chromeOptions)

########################################Passing the required url
f.get("http://%s/" % (url))
e = WebDriverWait(f, 100).until( EC.presence_of_element_located((By.ID, "login_user")))#f.find_element_by_id("login__username")
e.send_keys(user)
e = WebDriverWait(f, 100).until( EC.presence_of_element_located((By.ID, "login_cred")))#f.find_element_by_id("login__password")
e.send_keys(pass)
e = f.find_element_by_id("c-login-btn")
e.send_keys(keys.Keys.ENTER)

e = WebDriverWait(f, 100).until( EC.presence_of_element_located((By.ID, "campaign-tab")))
f.find_element_by_xpath('//*[contains(text(), "ABC")]').click()
f.find_element_by_xpath("//*[contains(text(), " + " '" + Org + "'" + ")]").click()
#e = f.find_element_by_id("user-settings")
#e.click()
sleep(2)
f.get("XYZ")
#e = f.find_element_by_id("search import file")
#e.send_keys(keys.Keys.ENTER)
f.find_element_by_xpath('//*[@title="ABC"]').click()
f.find_element_by_xpath('//*[@title="ABCD"]').click()
f.find_element_by_xpath('//*[@title="ABCDE"]').click()
sleep(1)
#e = WebDriverWait(f, 100).until( EC.presence_of_element_located((By.ID, "campaign-tab")))
e = f.find_element_by_id("search_by_date_org")
e.send_keys(Org)
e = f.find_element_by_id("search_by_date__profile")
#e.send_keys(profile)
f.find_element_by_xpath("//*[contains(text()," + " '" + profile + "'" + ")]").click()
e = f.find_element_by_id("search_by_date__status")
e.send_keys("SUCCESS")
f.find_element_by_id("search_by_date__from").click()
sleep(1)
f.find_element_by_xpath('//*[@class="ui-datepicker-month"]').click()
f.find_element_by_xpath("//*[contains(text()," + " '" + str(start_month) + "'" + ")]").click()
f.find_element_by_xpath('//*[@class="ui-datepicker-year"]').click()
f.find_element_by_xpath("//*[contains(text()," + " '" + str(start_year) + "'" + ")]").click()

f.find_element_by_xpath("//a[@class='ui-state-default'][contains(text()," + " '" + str(start_day) + "'" + ")]").click()

sleep(1)
f.find_element_by_id("search_by_date__to").click()
sleep(1)
f.find_element_by_xpath('//*[@class="ui-datepicker-month"]').click()
f.find_element_by_xpath("//*[contains(text()," + " '" + str(end_month) + "'" + ")]").click()
f.find_element_by_xpath('//*[@class="ui-datepicker-year"]').click()
f.find_element_by_xpath("//*[contains(text()," + " '" + str(end_year) + "'" + ")]").click()
f.find_element_by_xpath("//a[@class='ui-state-default'][contains(text()," + " '" + str(end_day) + "'" + ")]").click()
f.find_element_by_id("search_by_date__submit").click()
sleep(2)
f.find_element_by_xpath("//select[@name='table_view_length']/option[@value='100']").click()

########################################Storing all the links which is needed for the download
links = [link.get_attribute('href') for link in f.find_elements_by_xpath('//td/a[starts-with(@href, "")]')]
for i in links:
    f.get(i)
    f.find_element_by_id("search_file").click()
    f.find_element_by_xpath("//*[@value=" + " '" + re.findall('\d+',i)[1] + "'" + "]").click()
    f.find_element_by_id("search_imported_file__submit").click()
    sleep(4)
    f.find_element_by_xpath('//*[contains(text(), "Download Reports")]').click()
    x= [z.get_attribute('href') for z in f.find_elements_by_xpath('//td/a[contains(@href, "error_summary")]')]
    if x:
        f.get(x[0])
        f.find_element_by_id("download_fs_file__submit").click()
    sleep(4)

f.close()   
    
    


########################################Filtering columns from the file. Providing only the required fields to the client.
col_del=['a','b','c','d','e','f','g','h']
path =r'C:\\Python27\\Raw_Error_Files\\' # use your path
allFiles = glob.glob(path + "/*.csv")
frame = pd.DataFrame()
list_ = []
for file_ in allFiles:
    df = pd.read_csv(file_,index_col=None, header=0,sep='","',converters={'mobile':str})
    col_extrac=[]
    headers=[]
    data=df.replace(np.nan,'', regex=True)

    for i in list(df.columns):
        if i not in col_del:
            headers.append(i)
            col_extrac.append(df[i].values.tolist())
    req_data=[]
    col_list=[]
    print file_
    file_id=re.findall('\d+', file_)
    print file_id[1]
    with open(ftp_files+file_id[1]+'_' + str(datetime.datetime.now().strftime("%Y-%m-%d")) + '_error_log.csv', 'wb') as fp:
        print headers
        for l in range(0,len(headers)):
            if l<>len(headers)-1:
                fp.write('"' + str(headers[l]) + '",')
            else:
                fp.write('"' + str(headers[l]) + '"' + '\n')
        for j in range(0,len(col_extrac[0])):
            for i in range(0,len(col_extrac)):
                req_data.append(str(col_extrac[i][j]))
            fp.write(str(req_data).replace('"','').replace('[','').replace(']','').replace('\'','"') + '\n')
            req_data=[]
    list_.append(req_data)     

######################################## Moving the required files to processed_files
src_files = os.listdir(raw_input_files)
for file_name in src_files:
    full_file_name = os.path.join(raw_input_files, file_name)
    if (os.path.isfile(full_file_name)):
        shutil.move(full_file_name, processed_files)






########################################FTP File Transfer 




########################################Provide your credentials and the required connection details:
USER = 'abc'
PASS = 'abc'

SERVER = 'data.capillarydata.com'
PORT = 21
BINARY_STORE = True # if False then line store (not valid for binary files (videos, music, photos...))


def print_line(result):
    print(result)

def connect_ftp():
    #Connect to the server
    ftp = FTP()
    ftp.connect(SERVER, PORT)
    ftp.login(USER, PASS)
    
    return ftp

def upload_file(ftp_connetion,  upload_file_path):

    #Open the file
    try:
        upload_file = open(upload_file_path, 'r')
        
        #get the name
        path_split = upload_file_path.split('\\')
        print path_split
        final_file_name = path_split[len(path_split)-1]
        #transfer the file
        print('Uploading ' + final_file_name + '...')
        
        if BINARY_STORE:
            ftp_connetion.cwd("/Data_Import/Landmark/")
            ftp_connetion.storbinary('STOR '+ final_file_name, upload_file)
        else:
            ftp_connetion.cwd("/Data_Import/Landmark/")  
            ftp_connetion.storlines('STOR '+ final_file_name, upload_file)
            
        print('Upload finished.')
        
    except IOError:
        print ("No such file or directory... passing to next file")

    
##################Take all the files and upload all
ftp_conn = connect_ftp()

##################Uploading all the files to the specified folder
files_to_be_uploaded = glob.glob(ftp_files + "/*.csv")

for upload_ftp in files_to_be_uploaded:
    upload_file(ftp_conn, upload_ftp)

src_files = os.listdir(ftp_files)
for file_name in src_files:
    full_file_name = os.path.join(ftp_files, file_name)
    if (os.path.isfile(full_file_name)):
        shutil.move(full_file_name, processed_files)    
		
