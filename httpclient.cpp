#include "httpclient.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
HttpClient::HttpClient(QObject *parent)
    : QObject(parent)
{
    // 连接网络请求完成的信号
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &HttpClient::onFinished);
}

void HttpClient::sendGetRequest(QUrl url)
{
    //     networkManager = new QNetworkAccessManager();

    // 创建 GET 请求的 URL
    //("https://jsonplaceholder.typicode.com/posts/1");

    QNetworkRequest request(url);

    // 发送 GET 请求
    networkManager->get(request);
}

void HttpClient::sendPostRequest(QUrl url)
{

    // QUrl url("https://jsonplaceholder.typicode.com/posts");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 构造 JSON 数据
    QJsonObject json;
    json["title"] = "foo";
    json["body"] = "bar";
    json["userId"] = 1;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // 发送 POST 请求
    networkManager->post(request, data);
}
void HttpClient::printChache()
{
    // if (p_test != NULL)
    // {
    //     qDebug() << "Monitor Chache status:\n";
    //     qDebug() << p_test->bytes.length();
    //     // p_test->print();
    // }
}

void HttpClient::onFinished(QNetworkReply *reply)
{
    // 打印请求的 URL 和状态码
    qDebug() << "URL:" << reply->url().toString();
    qDebug() << "Status Code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // 检查是否有错误
    if (reply->error() == QNetworkReply::NoError)
    {
        // 请求成功，打印返回的内容
        QString response = reply->readAll();
        qDebug() << "Response:" << response;
    }
    else
    {
        // 请求失败，输出错误信息
        qDebug() << "Error:" << reply->errorString();
    }



    // 正确删除 QNetworkReply
    reply->deleteLater();
}
