import sys
import mysql.connector

if len(sys.argv) < 1 :
  sys.exit(0) ;

db = mysql.connector.connect(
  host="192.168.0.97",
  user="foxman",
  passwd="la0marina",
  database="erp"
)

mc = db.cursor()

ss = "select * from `erp`.`countries` where `used` > 0 order by `id` asc;" ;

mc.execute(ss)

for x in mc:
  if x[5] == None:
    two = "" ;
  else:
    two = x[5].decode("utf-8") ;
  if x[6] == None:
    three = "" ;
  else:
    three = x[6].decode("utf-8") ;
  if x[7] == None:
    four = "" ;
  else:
    four = x[7].decode("utf-8") ;
  if x[8] == None:
    name = "" ;
  else:
    name = x[8].decode("utf-8") ;
  print("{",x[0],",",x[1],",",x[2],",",x[3],",",x[4],",\"",two,"\",\"",three,"\",\"",four,"\",\"",name,"\"},") ;
