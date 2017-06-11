#  Created by Emre Özdil
#  Copyright © 2014 Emre Özdil. All rights reserved.

import bottle
import datetime
import pytz

global saved

saved= ''


def index(title,content):
    index= "<!DOCTYPE html>\n"
    index=index+"<html>\n"
    index=index+"    <head>\n"
    index=index+"        <title>"+title+"</title>\n"
    index=index+"        <meta charset="+"utf-8"+" />\n"
    index=index+'        <link rel="stylesheet" type="text/css" href= "static/blog.css"/>\n'
    index=index+"    </head>\n"
    index=index+"    <body>\n"
    index=index+'        <ul class="menu_bar">'
    index=index+'            <li class="menu_bar"><a href="/">Home</a></li>'
    index=index+'            <li class="menu_bar"><a href="/show">Messages</a></li>'
    index=index+'            <li class="menu_bar"><a href="/times">Times</a></li>'
    index=index+'        </ul>'
    index=index+content
    index=index+"    </body>\n"
    index=index+"</html>"
    return index


@bottle.route('/show')
def show():
    global saved
    return index('Hello', saved)

def time_now(place_name):
    place=pytz.timezone(place_name)
    now_time=datetime.datetime.now(place).strftime("%H:%M  %d/%m/%y")
    return now_time
@bottle.route('/time', method="GET")
def time_page():
    place = bottle.request.GET.get('place')
    place_time = time_now(place)
    time = '<b><i>The current time in ' + place + ' is: ' + str(place_time) + '</b></i>\n'
    return index('time', time)


@bottle.route('/times')
def index_page():
    content = '    <p>Show me the time in:</p>\n'
    content = content + '    <div class="times"><ol>\n'
    for (len(pytz.all_timezones)):
        time=pytz.all_timezones[i]
        part=time.split('/')
        city=part[len(part)-1]
        content=content + '                        <li class="times"><a href="/time?place='+ time +'">'+ city +'</a></li>\n'
        i=i+1
    content = content + '    </ol></div>\n'
    return index('time', content)
@bottle.route("/save", method='POST')
def save():
    global saved
    gender=bottle.request.POST.get('opt')
    if gender== "Male":
        gender="Mr. "
    elif gender=="Female":
        gender= "Ms. "
    else:
        gender=''
    place=bottle.request.POST.getall('city')
    i=0
    while i<len(place):
        place_time=time_now(place[i])
        time='The current time in ' + place[i] + ' is: ' + str(place_time)
        i=i+1

    first_name=bottle.request.POST.get('textname')
    surname=bottle.request.POST.get('textsurname')
    message=bottle.request.POST.get('msg')

    if first_name=='':
        if surname=='':
            return index('Error', 'Please  enter a name and surname, it is necessary to send message!<br><a href="/" >Go to home page</a>')
        else:
            return index('Error', 'Please enter a name, it is neccessary to send a message!<br><a href="/" >Go to home page</a>')
    elif surname=='':
        return index('Error', 'Please enter a surname, it is neccessary to send a message!<br><a href="/" >Go to home page</a>')
    else:

        saved= saved + gender + first_name + ' ' + surname + ' said that' + '<br>' + message  + '<br>' + time + '<hr>'
        content='<h2>Your message was saved<br><br>In order to access homepage and see all messages <a href="/" >click</a><h2>'
        return index("saved", content)

@bottle.route("/")
def default():
    content='        <h1>Welcome</h1>\n'
    content=content + '        <div class="field">\n'
    content=content + '            <fieldset><legend>Homework BIL103E</legend>\n'
    content=content + '                <form action="/save" method="post">\n'
    content=content + '                    <table>\n'
    content=content + '                        <tr><td>Name:<input type="text" name="textname"/></td></tr>\n'
    content=content + '                        <tr><td>Surname:<input type="text" name="textsurname"/></td></tr>\n'
    content=content + '                    </table>\n'
    content=content + '                    Gender: Male<input type="radio" name="opt" value="Male"/>\n'
    content=content + '                    Female<input type="radio" name="opt" value="Female"/><br>\n'
    content=content + '                    Location: <select name="city" size="1">\n'
    i=0
    while i<len(pytz.all_timezones):
        time=pytz.all_timezones[i]
        part=time.split('/')
        city=part[len(part)-1]
        content=content + '                        <option value='''+ time +'>'+ city +'</option>\n'
        i=i+1
    content=content + '                    </select>\n'
    content=content + '                    <br>Message:<br>\n'
    content=content + '                    <textarea name="msg" cols="40" rows="10"></textarea><br><br>\n'
    content=content + '                    <input type="submit" value="Send"/>\n'
    content=content + '                    <input type="reset" value="Reset"/>\n'
    content=content + '                </form>\n'
    content=content + '            </fieldset>\n'
    content=content + '        </div>\n'
    content=content + saved

    return index('Home Page', content)

@bottle.route("/static/blog.css")
def css():
    mycss= bottle.static_file("blog.css",root="/home/ozdile/mysite/static/")
    return mycss

bottle.run(host="localhost", port="8080")
#application=bottle.default_app()
