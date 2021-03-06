# dotoo
A simple client-server todo application. 

## Client-side (GUI)
The client-side visualizes the server data. Currently two data sets are available: Tasks and persons. 

GUI will provide following features:
- See all task or filter or sort them to get a better overview
- Create new tasks: Attach additional information as responsibility, due date, priority, etc.
- Change existing tasks (mark as done, move responsibility to an other employee)
- Delete existing tasks
- See the tasks of the other persons like your employees or friends
- See all existing persons within system

## Server-side
The server-side delivers the main data by running a http server (without ssl). Here are the main features of the server:
- Using a easy-to-use REST-API to get data or change them
- All CRUD methods for person and tasks
- Data is provided in JSON format, but format range is very extensible

## REST-API
Currently there are two collection resources '/tasks' and '/persons'. To access particular resources, use '/tasks/<id>' respective '/persons/<id>'. (An Id starts at '1'. The Id '0' is invalid within this REST-API.)

### /tasks
#### Get all tasks: 
- Req-Header: GET /tasks
- Res-Body: { { "id": <id>, "is_done" <bool>, "comment": <string>, "due_date": <string> }, { "id": <id>, ... } }

#### Get one task:
- Req-Header: GET /tasks/<id>
- Res-Header: Http status code
- Res-Body: { "id": <id>, "is_done" <bool>, "comment": <string>, "due_date": <string>, ... }
  
#### Create a new task:
- Req-Header: POST /tasks/<id>
- Req-Body: { "is_done" <string>, "due_date": <string>, "comment": <string>, "creator": <id>, ... }
- Res-Header: Http status code

#### Change an existing task:
- Req-Header: PUT /tasks/<id>
- Req-Body: { "is_done" <string>, "due_date": <string>, "comment": <string>, "creator": <id>, ... }
- Res-Header: Http status code

#### Delete an existing person:
- Req-Header: DELETE /tasks/<id>
- Res-Header: Http status code

### /persons
#### Get all persons: 
- Req-Header: GET /persons
- Res-Body: { { "id": <id>, "forename" <string>, "name": <string>, "comment": <string> }, { "id": <id>, ... } }

#### Get one person:
- Req-Header: GET /persons/<id>
- Res-Header: Http status code
- Res-Body: { "id": <id>, "forename" <string>, "name": <string>, "comment": <string> }
  
#### Create a new person:
- Req-Header: POST /persons/<id>
- Req-Body: { "forename" <string>, "name": <string>, "comment": <string> }
- Res-Header: Http status code

#### Change an existing person:
- Req-Header: PUT /persons/<id>
- Req-Body: { "forename" <string>, "name": <string>, "comment": <string> }
- Res-Header: Http status code

#### Delete an existing person:
- Req-Header: DELETE /persons/<id>
- Res-Header: Http status code



## Used external code
- Http webserver: https://github.com/nikhilm/qhttpserver
- For parsing json: https://github.com/nlohmann/json
