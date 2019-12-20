(($) => {
  $.fn.drag = function (options) {
    const $this = this

    let $current, currPos = null

    $this.addClass("drag").mousedown(function (event) {
      $current = $(this)
      currPos = {
        x: $current.offset().left + $current.outerWidth() - event.pageX,
        y: $current.offset().top + $current.outerHeight() - event.pageY  
      }
    }).css("cursor", "move")

    $(document).mousemove(event => {
      if ($current) {  
        let newPos = {
          x: event.pageX + currPos.x - $current.outerWidth(), 
          y: event.pageY + currPos.y - $current.outerHeight()
        }

        $current.offset({
          top: newPos.y,
          left: newPos.x
        })

        if ($.isPlainObject(options) && $.isFunction(options.change)) {
          options.change.call($current, currPos, newPos)
        }
      }
    }).mouseup(() => {
      $current = null
    })

    return $this
  }
})(jQuery)
