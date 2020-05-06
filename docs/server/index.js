const express = require('express')
const { exec } = require('child_process')
const bodyParser = require('body-parser')
const fs = require('fs')
const temp = require('temp')
const path = require('path')
const cors = require('cors')

const PORT = 3000

const app = express()
app.use(bodyParser.json())
app.use(cors())

temp.track()

app.post('/run', (req, res) => {
    const code = req.body.code
    const { path, fd } = temp.openSync();
    fs.writeSync(fd, code)
    fs.closeSync(fd)
    const f2 = temp.openSync();
    fs.closeSync(f2.fd)
    console.log(code)
    exec(`timeout 5 ../build/src/Ero_run ${path} ${f2.path} 1>/dev/null; timeout 5 ${f2.path}`, (error, stdout, stderr) => {
        temp.cleanupSync()
        if (error) {
            res.status(400).send({
                error: stderr
            })
        }
        else {
            res.send({
                data: stdout
            })
        }
    })
})

app.listen(PORT, () => {
    console.log(`Server is listening at http://localhost:${PORT}`)
})
