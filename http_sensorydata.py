import pandas as pd 
url = "http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=80" #Oma groupID68. Omassa tietokannassa väärää dataa, joten sain luvan käyttää Igor Karppisen dataa
csv = pd.read_csv(url,delimiter=';')
csv.to_csv('groupid68data.csv')
print("tiedosto luotu")
