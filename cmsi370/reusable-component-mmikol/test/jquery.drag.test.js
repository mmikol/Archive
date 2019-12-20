describe('Drag jQuery plugin', () => {
  const options = {
    change: () => {
      // No-op; Jasmine spy will check on whether this got called.
    }
  }

  beforeEach(() => {
    fixture.setBase('test')
    fixture.load('jquery.drag.fixture.html')
  })

  afterEach(() => fixture.cleanup())

  it('should return itself and change the cursor when plugin is installed', () => {
    const $target = $('.drag-test')
    const $pluginResult = $target.drag(options)

    expect($pluginResult).toBe($target)
    expect($pluginResult.attr('style')).toBe('cursor: move;')
  })

  let positionUpdateTest = () => {
    // Set initial offset position
    $('.drag-test').offset({
      top: 100,
      left: 100
    })

    const mousedown = $.Event('mousedown', { pageX: 100, pageY: 100 })
    $('.drag-test').trigger(mousedown)
    
    let mousemove = $.Event('mousemove', { pageX: 10 })
    $('.drag-test').trigger(mousemove)

    expect($('.drag-test').offset().left).toBe(10)
    expect($('.drag-test').offset().top).toBe(100)

    mousemove = $.Event('mousemove', { pageY: 30 })
    $('.drag-test').trigger(mousemove)

    expect($('.drag-test').offset().top).toBe(30)
    expect($('.drag-test').offset().left).toBe(10)

    $('.drag-test').trigger($.Event('mouseup'))
  }

  describe('installed behavior', () => {
    beforeEach(() => $('.drag-test').drag())

    it('should change positions correctly', positionUpdateTest)
  })
})
