const express = require('express')
const path = require('path')
const app = express()

const PORT = 3000

app.get('/', (req, res) => res.sendFile(path.join(__dirname, '../public/index.html')))

app.listen(PORT, '0.0.0.0', () => console.log(`Listing on ${PORT}`))
