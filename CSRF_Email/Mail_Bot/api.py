
import json
import falcon
from wsgiref import simple_server
from db_helpers import *
from html_evaluator import *

class ReceiveBotMail:

    def on_post(self, req, resp):

        data = req.stream.read(4096).decode('utf-8')
        data = json.loads(data)
        team_id = data['team_id']
        team_name = data['team_name']
        email = data['email']
        mail_body = data['mail_body']

        store_mail_body(email, team_name, mail_body)
        k = team_name + get_rand_str()
        k = get_md5(k)
        filename = team_name + "_" + k + ".html"

        with open('mails/' + filename, 'w') as f:
            f.write(mail_body)

        print("File written ... ")

        evaluate_mail(filename)
        print("Mail evaluated ...")
        response = {}

        response = json.dumps(response)
        resp.body = response


api = falcon.API()
# api.req_options.auto_parse_form_urlencoded = True
api.add_route('/evaluate', ReceiveBotMail())

httpd = simple_server.make_server('127.0.0.1', 9000, api)
httpd.serve_forever()
