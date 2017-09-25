import MySQLdb as sql

outfile1 = open('testXML1.xml', 'w')
outfile2 = open('testXML2.xml', 'w')
outfile3 = open('testXML3.xml', 'w')
# Open database connection
db = sql.connect("localhost","root","","eldercare" )

def outfileName1():
    sql1 = ("SELECT * FROM elder")
    #sql2 = ("SELECT * FROM keeper where k_age < 38")
    #sql3 = ("SELECT e_name,k_name FROM elder INNER JOIN care ON elder.e_id = care.e_id INNER JOIN keeper ON care.k_id = keeper.k_id")

    # prepare a cursor object using cursor() method
    cursor = db.cursor()

    # execute SQL query using execute() method.
    cursor.execute(sql1)

    # Fetch a single row using fetchone() method.
    data = cursor.fetchall()
    outfile1.write('<?xml version="1.0" ?>\n')
    outfile1.write('<AllElder>\n')
    for row in data:
        outfile1.write('  <elder>\n')
        outfile1.write('    <num>%s</num>\n' % row[0])
        outfile1.write('    <age>%s</age>\n' % row[1])
        outfile1.write('    <addr>%s</addr>\n' % row[2])
        outfile1.write('    <name>%s</name>\n' % row[3])
        outfile1.write('  </elder>\n')
    outfile1.write('</AllElder>\n')
    outfile1.close()

def outfileName2():
    sql2 = ("SELECT * FROM keeper where k_age < 38")
    #sql3 = ("SELECT e_name,k_name FROM elder INNER JOIN care ON elder.e_id = care.e_id INNER JOIN keeper ON care.k_id = keeper.k_id")

    # prepare a cursor object using cursor() method
    cursor = db.cursor()

    # execute SQL query using execute() method.
    cursor.execute(sql2)

    # Fetch a single row using fetchone() method.
    data = cursor.fetchall()
    outfile2.write('<?xml version="1.0" ?>\n')
    outfile2.write('<keeper>\n')
    for row in data:
        outfile2.write('  <Profile>\n')
        outfile2.write('    <num>%s</num>\n' % row[0])
        outfile2.write('    <name>%s</name>\n' % row[1])
        outfile2.write('    <age>%s</age>\n' % row[2])
        outfile2.write('    <tel>%s</tel>\n' % row[3])
        outfile2.write('  </Profile>\n')
    outfile2.write('</keeper>\n')
    outfile2.close()

def outfileName3():
    sql3 = ("SELECT e_name,k_name FROM elder INNER JOIN care ON elder.e_id = care.e_id INNER JOIN keeper ON care.k_id = keeper.k_id")

    # prepare a cursor object using cursor() method
    cursor = db.cursor()

    # execute SQL query using execute() method.
    cursor.execute(sql3)

    # Fetch a single row using fetchone() method.
    data = cursor.fetchall()
    outfile3.write('<?xml version="1.0" ?>\n')
    outfile3.write('<mydata>\n')
    for row in data:
        outfile3.write('  <elderAndkeeper>\n')
        outfile3.write('    <nameElder>%s</nameElder>\n' % row[0])
        outfile3.write('    <nameKeeper>%s</nameKeeper>\n' % row[1])
        outfile3.write('  </elderAndkeeper>\n')
    outfile3.write('</mydata>\n')
    outfile3.close()
# disconnect from server
outfileName1()
outfileName2()
outfileName3()
db.close()
