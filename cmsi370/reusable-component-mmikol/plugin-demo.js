$(() => {
  let $log = $(".event-log")
  let logEvent = (message) => {
    $log.text($log.text() + message + "\n")
        .scrollTop($log[0].scrollHeight - $log.height())
  }

  $(".drag-this").drag({
    change: function (oldPosition, newPosition) {
      logEvent(JSON.stringify(oldPosition) + " to " + JSON.stringify(newPosition))
    }
  })
})
