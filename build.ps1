
$winmd = 'C:\Program Files (x86)\Windows Kits\10\UnionMetadata\Windows.winmd'
$outdir = $PsScriptRoot + '\prebuilt'

NodeRTCmd `
    --namespace 'Windows.Data.Xml.Dom' `
    --winmd $winmd `
    --outdir $outdir

NodeRTCmd `
    --namespace 'Windows.UI.Notifications' `
    --winmd $winmd `
    --outdir $outdir
