package main

import (
  "fmt"
  "io/ioutil"
  "net/http"
  "os"
  "bytes"
  "encoding/json"
)

func check(e error) {
  if e != nil {
    fmt.Println(e)
    os.Exit(1)
  }
}

func main() {
  url := "kgsearch.googleapis.com/v1/entities:search"

  if len(os.Args) != 2 {
    fmt.Println("google [ name ]")
  }
  query := os.Args[1]
  key := "AIzaSyAb_N1cD6zJ1GLwbqF2VTfrz39amyUOh7s"
  resp, err := http.Get(fmt.Sprintf("https://%s?query=%s&key=%s", url, query, key))
  check(err)
  defer resp.Body.Close()
  readBody, err := ioutil.ReadAll(resp.Body)
  check(err)
  readBody = bytes.ReplaceAll(readBody, []byte("itemListElement"), []byte("ItemList"))
  readBody = bytes.ReplaceAll(readBody, []byte("name"), []byte("Name"))
  readBody = bytes.ReplaceAll(readBody, []byte("result"), []byte("Result"))
  readBody = bytes.ReplaceAll(readBody, []byte("description"), []byte("Description"))
  readBody = bytes.ReplaceAll(readBody, []byte("detailedDescription"), []byte("DetailedDescription"))
  readBody = bytes.ReplaceAll(readBody, []byte("articleBody"), []byte("ArticleBody"))
  type DetailedDescriptionT struct {
    ArticleBody string
  }
  type ResultT struct {
    Name string
    Description string
    DetailedDescription DetailedDescriptionT
  }
  type ItemListT struct {
    Result ResultT
  }
  type Data struct {
    ItemList []ItemListT
  }
  var data Data
  err = json.Unmarshal(readBody, &data)
  check(err)
  for _, item := range(data.ItemList) {
    fmt.Println(item.Result.Name)
    fmt.Println(item.Result.DetailedDescription.ArticleBody)
    break
  }
}
