
import json
import falcon
from wsgiref import simple_server
from auth import auth_user, get_team_details, auth_team_name

class EmailAuth:

    def on_post(self, req, resp):

        data = req.stream.read().decode('utf-8')
        data = json.loads(data)
        email = data['email']
        password = data['password']

        response = {}
        if auth_user(email, password):
            response = get_team_details(email)
            response['is_valid'] = True
        else:
            response['is_valid'] = False

        response = json.dumps(response)
        resp.body = response

class TeamNameAuth:

    def on_post(self, req, resp):

        data = req.stream.read().decode('utf-8')
        data = json.loads(data)
        team_name = data['team_name']
        password = data['password']

        response = {}
        if auth_team_name(team_name, password):
            response['is_valid'] = True
        else:
            response['is_valid'] = False

        response = json.dumps(response)
        resp.body = response


api = falcon.API()
api.add_route('/email_auth', EmailAuth())
api.add_route('/team_name_auth', TeamNameAuth())

httpd = simple_server.make_server('127.0.0.1', 8000, api)
httpd.serve_forever()
