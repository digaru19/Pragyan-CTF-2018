
from mysql.connector import MySQLConnection, Error
from db_helpers import *
import bcrypt

conn = None

def connect():
    db_config = read_db_config()

    try:
        conn = MySQLConnection(**db_config)

        if not conn.is_connected():
            raise Error('Connection failed.')
        return conn

    except Error as error:
        print(error)

def auth_user(email, password):
    cur = conn.cursor()
    passwd_hash = get_passwd_hash(cur, email)
    if passwd_hash is None:
        return False

    valid = bcrypt.checkpw(password.encode(), passwd_hash.encode())

    return valid

def get_team_details(email):
    cur = conn.cursor()
    query = "SELECT id, team_name FROM users where email=%s"
    args = (email, )

    cur.execute(query, args)
    row = cur.fetchone()

    if row is None:
        return None

    resp = {}
    resp['team_id'] = row[0]
    resp['team_name'] = row[1]

    return resp


conn = connect()
