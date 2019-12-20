describe('recipes search example', () => {
  beforeEach(() => {
    fixture.setBase('test')
    fixture.load('search.fixture.html')
    window.SpoonacularSearchHandler.init()
  })

  afterEach(() => fixture.cleanup())

  it('should start with an empty search field', () => expect($('#searchTerm').val()).toBe(''))
  it('should start with a disabled search button', () => expect($('#searchButton').prop('disabled')).toBe(true))

  describe('search button', () => {
    let searchTerm
    let searchButton

    beforeEach(() => {
      searchTerm = $('#searchTerm')
      searchButton = $('#searchButton')
    })

    it('should be enabled when the search field is not blank', () => {
      searchTerm.val('i can haz unit tests').trigger('input')
      expect(searchButton.prop('disabled')).toBe(false)
    })

    it('should be disabled when the search field is blank', () => {
      searchTerm.val('').trigger('input')
      expect(searchButton.prop('disabled')).toBe(true)
    })
  })

  const FETCH_COMPLETION_DELAY = 250

  describe('API calls', () => {
    beforeEach(() => {
      sinon.stub(window.ApiService, 'searchRecipes')

      window.ApiService.searchRecipes.returns(Promise.resolve({
        "results": [{
          "id": 667024,
          "title": "Simple Spaghetti Fra Diavolo"
        }]
      }))

      $('#searchTerm').val('test')
      $('form.searchForm').submit()
    })

    afterEach(() => window.ApiService.searchRecipes.restore())

    it('should trigger a search when the search button is clicked', () =>
      expect(window.ApiService.searchRecipes.firstCall.args[0]).toEqual({
        query: 'test',
        number: 15
      })
    )

    it('should populate the result container upon receiving results', done => setTimeout(() => {
      expect($('.searchResultList').children().length).toBe(1)
      done()
    }, FETCH_COMPLETION_DELAY))
  })

  describe('failed API calls', () => {
    beforeEach(() => {
      sinon.stub(window.ApiService, 'searchRecipes')
      window.ApiService.searchRecipes.returns(Promise.reject('Mock failure'))

      $('#searchTerm').val('hello failure')
      $('form.searchForm').submit()
    })

    afterEach(() => window.ApiService.searchRecipes.restore())

    it('should display an alert when the API call fails', done => setTimeout(() => {
      expect($('#searchResultContainer').find('.alert.alert-danger').length).toBe(1)
      done()
    }, FETCH_COMPLETION_DELAY))
  })
})