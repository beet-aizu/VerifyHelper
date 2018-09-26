import requests, requests.utils
import texttable
import argparse
import pickle
import re
import os
	
from getpass import getpass
from datetime import datetime, timedelta
from time import sleep

parser = argparse.ArgumentParser()

parser.add_argument('--login', action='store_true')
parser.add_argument('--logout', action='store_true')
parser.add_argument('--session', action='store_true')
parser.add_argument('--verify', type=str, required=False, default='$')
parser.add_argument('--submit', type=str, required=False, default='$')
parser.add_argument('--result', action='store_true')

args = parser.parse_args()

endpoint = 'https://judgeapi.u-aizu.ac.jp'

def login(id, password):
    URI = '/session'
    data = {
        'id': id,
        'password': password,
    }
    res = requests.post(endpoint + URI, json = data)
    
    with open('.session', mode = 'wb') as f:
        pickle.dump(requests.utils.dict_from_cookiejar(res.cookies), f)

    with open('.user', mode = 'wb') as f: pickle.dump(id, f)

    with open('.language', mode = 'wb') as f:
        return pickle.dump(res.json()['defaultProgrammingLanguage'], f);
    
def load_cookies():
    with open('.session', mode = 'rb') as f:
        return requests.utils.cookiejar_from_dict(pickle.load(f))

def load_id():
    with open('.user', mode = 'rb') as f: return pickle.load(f);
    
def load_language():
    with open('.language', mode = 'rb') as f: return pickle.load(f);

def resolve_include(solution):
    pattern = re.compile('#include \".*\.cpp\"$', flags=(re.MULTILINE))
    if pattern.search(solution):
        result = pattern.search(solution).span()
        include = os.path.basename(solution[result[0]+10:result[1]-1])
        with open(include) as f:
            s = f.read()
            l = s.find('//BEGIN CUT HERE') + 17
            r = s.find('//END CUT HERE')
            return resolve_include(pattern.sub(s[l:r], solution, 1))
    return solution

def resolve_problemId(solution):
    base = 'problemId='
    result = re.search(base + '.*$', solution, flags=(re.MULTILINE)).span()
    return solution[result[0]+len(base): result[1]]
    
def session():
    URI = '/self'
    cookies = load_cookies()
    res = requests.get(endpoint + URI, cookies = cookies)
    print(res.json())

def wait_cooltime(cnt):
    if cnt != 0: sleep(2);
    sz = 8 if cnt == 0 else 1
    id = load_id()
    URI = '/submission_records/users/{}?size={}'.format(id, sz)
    res = requests.get(endpoint + URI)
    if len(res.json()) < sz: return;
    prev = datetime.fromtimestamp(res.json()[-1]['submissionDate'] // 1000)
    curr = datetime.now()
    if prev + timedelta(seconds = 70) < curr: return;
    d = prev + timedelta(seconds = 70) - curr
    print('Waiting for API Limits...')
    sleep(d.seconds)
    
def submit(solution):
    URI = '/submissions'
    cookies = load_cookies()
    language = load_language()
    
    problemId = resolve_problemId(solution)
    sourceCode = resolve_include(solution)
    
    data = {
        'problemId': problemId,
        'language': language,
        'sourceCode': sourceCode,
    }

    res = requests.post(endpoint + URI, cookies = cookies, json = data)
    token = res.json()['token']

submission_status = {0:'CE', 1:'WA', 2:'TLE', 3:'MLE', 4:'AC',
                     5:'WJ', 6:'OLE', 7:'RE', 8:'PE', 9:'RUN',}

def submission_records():
    id = load_id()
    URI = '/submission_records/users/{}?size={}'.format(id, 10)
    res = requests.get(endpoint + URI)
    table = texttable.Texttable(max_width=100)
    table.add_row([
        'Run#', 'Problem', 'Status', '%', 'Time', 'Memory', 'Code',
    ])
    for verdict in res.json():
        cpuTime = verdict['cpuTime']
        table.add_row([
            verdict['judgeId'],
            verdict['problemId'],
            submission_status[verdict['status']],
            verdict['accuracy'],
            '{0:02d}:{1:02d}'.format(cpuTime // 100, cpuTime % 100),
            '{0:6d} KB'.format(verdict['memory']),
            '{0:5d} B'.format(verdict['codeSize']),
        ])
         
    print(table.draw())
    
if args.login:
    id = input('username: ')
    password = getpass('password: ')
    login(id, password)

if args.logout:
    f = open('.session', 'w')
    f.close()
    f = open('.user', 'w')
    f.close()
    f = open('.language', 'w')
    f.close()

if args.session:
    session()

if args.verify != '$':
    with open(args.verify) as f:
        s = f.read()
        l = s.find('BEGIN VERIFY') + 12
        r = s.find('END VERIFY')
        cnt = 0
        for i in s[l:r].split(','):
            p = os.path.basename(i.strip())
            if p == '': continue;
            path = './verify/' + p
            
            flg = os.path.exists(path)
            print(p, ':', 'Found' if flg else 'Not Found')
            
            if flg:
                if cnt % 8 == 0: wait_cooltime(cnt);
                with open(path) as g: submit(g.read());
                cnt = cnt + 1
                
if args.submit != '$' :
    with open(args.submit) as f: submit(f.read());

if args.result:
    submission_records()
