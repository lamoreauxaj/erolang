const express = require('express')

const app = express()

const PORT = 3000

app.get('/', (req, res) => {
    res.send('Hello world! I hope this works Anand!')
})

app.listen(PORT, () => {
    console.log(`Server is listening at http://localhost:${PORT}`)
})