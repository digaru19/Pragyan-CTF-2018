
from configparser import ConfigParser

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

def get_passwd_hash(cur, email):
    query = "SELECT passhash FROM users where email=%s"
    args = (email, )

    cur.execute(query, args)
    row = cur.fetchone()

    if row is None:
        return None

    return row[0]

def get_email_from_teamname(cur, team_name):
    query = "SELECT email from users where team_name=%s"
    args = (team_name, )

    cur.execute(query, args)
    row = cur.fetchone()

    if row is None:
        return None

    return row[0]
