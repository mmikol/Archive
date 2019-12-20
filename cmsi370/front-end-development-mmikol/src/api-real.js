(() => {
  let api = 'https://api.spoonacular.com/'
  const API_KEY = '435336eb1c974482929085fce4a7c0f2'

  const apiHost = host => { api = host }
  const urlFor = resource => `${api}${resource}`

  const HTTP_OK = 200

  const throwResponseError = response => {
    const error = new Error(response.statusText)
    error.response = response
    throw error
  }

  const emitNativeError = error => {
    throw error
  }

  const statusCheck = successStatuses => response => {
    if (successStatuses.includes(response.status)) {
      return response
    } else {
      throwResponseError(response)
    }
  }

  const okCheck = statusCheck([HTTP_OK])

  const headers = {
    'Content-Type': 'application/json'
  }

  const paramsWithApiKey = params => {
    const result = new URLSearchParams(params)
    result.set('apiKey', API_KEY)
    return result
  }

  const query = (resource, params) => fetch(`${urlFor(resource)}?${paramsWithApiKey(params)}`, {
    headers
  }).then(okCheck, emitNativeError)
    .then(response => response.json())

  const searchRecipes = params => query('recipes/search', params)
  const createMealPlan = params => query('recipes/mealplans/generate', params)
  const getRecipeInfo = id => query(`recipes/${id}/information`)
  const getNutritionFacts = id => query(`recipes/${id}/nutritionWidget.json`)

  window.ApiService = {
    apiHost,
    searchRecipes,
    createMealPlan,
    getRecipeInfo,
    getNutritionFacts
  }
})()