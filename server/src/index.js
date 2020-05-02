const express = require('express')
const { exec } = require('child_process')
const bodyParser = require('body-parser')
const fs = require('fs')
const temp = require('temp')
const path = require('path')
const app = express()

temp.track()

const PORT = 3000

app.use(bodyParser())

app.post('/api/run', (req, res) => {
    const code = req.body.code
    out = '4.2\n4.7\n'
    const { path, fd } = temp.openSync();
    fs.writeSync(fd, code)
    fs.closeSync(fd)
    const f2 = temp.openSync();
    fs.closeSync(f2.fd)
    exec(`../build/src/Ero_run ${path} ${f2.path} 1>/dev/null; ${f2.path}`, (error, stdout, stderr) => {
        temp.cleanupSync()
        res.send(stdout)
    })
})

app.get('/', (req, res) => res.sendFile(path.join(__dirname, '../public/index.html')))

app.listen(PORT, '0.0.0.0', () => console.log(`Listing on ${PORT}`))
