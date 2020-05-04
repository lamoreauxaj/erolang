const fs = require('fs')
const { execSync } = require('child_process')

exports.handler = async (event, context) => {
    try {
        const subject = event.queryStringParameters.name || 'World'
        // const f = fs.readFileSync('build/src/Ero_run')
        const res = execSync('./Ero_run 1.ero 1 --prod').toString()
        // exec('ls', (error, stdout, stderr) => {
        //     return {
        //         statusCode: 200,
        //         body: { error, stdout, stderr }
        //     }
        // })
        return {
            statusCode: 200,
            body: JSON.stringify( res )
        }
    } catch (err) {
        return { statusCode: 500, body: err.toString() }
    }
}
