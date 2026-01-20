from flask import Flask
import socket
import os

app = Flask(__name__)

@app.route('/')
def hello():
    hostname = socket.gethostname()
    commit = os.getenv('GIT_SHA', 'unknown')
    return f'''
    <h1>🚀 Hamilton DevOps Demo</h1>
    <p>Running on: <strong>{hostname}</strong></p>
    <p>Commit: <code>{commit[:8]}</code></p>
    <p>Registry: GitHub Container Registry</p>
    <hr>
    <p>Deployed via GitHub Actions → K3s on Raspberry Pi</p>
    '''

@app.route('/health')
def health():
    return {'status': 'healthy', 'service': 'hamilton-demo'}, 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
