#ifndef SCRIPTHIGHLIGHTER_H
#define SCRIPTHIGHLIGHTER_H
//------------------------------------------------------------------------------------
#include <QSyntaxHighlighter>
#include <QTextCharFormat>



QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE
//------------------------------------------------------------------------------------
//!
class ScriptHighlighter : public QSyntaxHighlighter
{
        Q_OBJECT

    public:
        ScriptHighlighter(QTextDocument *parent = 0);

    protected:
        void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };

        QVector<HighlightingRule> highlightingRules;

        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat unitFormat;
        QTextCharFormat keywordFormat;
        QTextCharFormat blockFormat;
        QTextCharFormat registerFormat;
        QTextCharFormat classFormat;
        QTextCharFormat singleLineCommentFormat;
        QTextCharFormat multiLineCommentFormat;
        QTextCharFormat quotationFormat;
        QTextCharFormat functionFormat;
};
//------------------------------------------------------------------------------------
#endif // SCRIPTHIGHLIGHTER_H
