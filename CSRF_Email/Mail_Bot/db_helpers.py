
from configparser import ConfigParser
from mysql.connector import MySQLConnection, Error

def read_db_config(filename='db.conf', section='mysql'):
    parser = ConfigParser()
    parser.read(filename)
 
    db = {}
    if parser.has_section(section):
        items = parser.items(section)
        for item in items:
            db[item[0]] = item[1]
    else:
        raise Exception('{0} not found in the {1} file'.format(section, filename))
 
    return db

def connect():
    db_config = read_db_config()
    try:
        conn = MySQLConnection(**db_config)
        if not conn.is_connected():
            raise Error('Connection failed.')
        return conn
    except Error as error:
        print(error)

def store_mail_body(email, team_name, mail_body):
    conn = connect()
    cur = conn.cursor()

    query = "INSERT INTO csrf_mail VALUES (DEFAULT, %s, %s, %s)"
    args = (email, team_name, mail_body,)
    cur.execute(query, args)

    conn.commit();
    return
