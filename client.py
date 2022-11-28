from cgi import print_directory
import pandas as pd
import matplotlib.pyplot as plt
import csv

connection = pd.read_csv("http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=68")
connection.fillna(0, inplace=True)

print(connection)